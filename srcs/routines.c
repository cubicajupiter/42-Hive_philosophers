/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:45 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:52:35 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void		main_routine(t_philo *p);
static void			*ph_solo(t_philo *p);
static int			ph_eat(t_philo *p, const int time_len, int *n_eaten);
static int			ph_idle(t_philo *p, const int time_len);

void	*dine(void *arg)
{
	t_philo			*philo;
	int				timeout;

	philo = (t_philo *)arg;
	timeout = 0;
	while (!mt_boolean_load(philo->is_running, philo->mutex[SIM]))
	{
		if (timeout++ == 7500)
			return (NULL);
		usleep(50);
	}
	if (philo->init_data[N_EAT] == 0)
		return (NULL);
	if (philo->init_data[N_PHILO] == 1)
		return (ph_solo(philo));
	if (philo->no % 2 == 1)
		usleep(150);
	main_routine(philo);
	return (NULL);
}

static inline void	main_routine(t_philo *p)
{
	int		n_eaten;

	n_eaten = 0;
	while (mt_boolean_load(p->is_running, p->mutex[SIM]))
	{
		if (p->no % 2 == 1)
		{
			if (!n_eaten)
				mt_putlog(get_time(*p->init_time), p->no, "is thinking\n", p->mutex[LOG]);
			else
				usleep(300);
		}
		if (ph_eat(p, p->init_data[TTO_EAT], &n_eaten) == DONE)
			break ;
		if (n_eaten == p->init_data[N_EAT])
			break ;
		if (ph_idle(p, p->init_data[TTO_SLEEP]) == DONE)
			break ;
		if (ph_idle(p, 0) == DONE)
			break ;
	}
}

static void	*ph_solo(t_philo *p)
{
	int64_t			timestamp;

	timestamp = get_time(*p->init_time);
	pthread_mutex_lock(p->mutex[L_FORK]);
	printf("%ld %d %s\n", timestamp, p->no, "has taken a fork");
	usleep(p->init_data[TTO_DIE] * 1000);
	timestamp = get_time(*p->init_time);
	return (NULL);
}

static int	ph_eat(t_philo *p, const int time_len, int *n_eaten)
{
	if (mt_boolean_load(p->is_running, p->mutex[SIM]) == false)
		return (DONE);
	if (mt_lock_forks(p->mutex[L_FORK], p->mutex[R_FORK], p) == DONE)
		return (DONE);
	p->last_eaten = get_time(*p->init_time);
	mt_putlog(p->last_eaten, p->no, "is eating\n", p->mutex[LOG]);
	usleep(time_len * 1000);
	mt_unlock_forks(p->mutex[L_FORK], p->mutex[R_FORK]);
	p->is_forkmtx[0] = false;
	p->is_forkmtx[1] = false;
	(*n_eaten)++;
	return (mt_boolean_load(p->is_running, p->mutex[SIM]) == false);
}

static int	ph_idle(t_philo *p, const int time_len)
{
	if (mt_boolean_load(p->is_running, p->mutex[SIM]) == false)
		return (DONE);
	if (time_len)
	{
		mt_putlog(get_time(*p->init_time), p->no, "is sleeping\n", p->mutex[LOG]);
		usleep(time_len * 1000);//it should be able to die while sleeping.
	}
	else
	{
		mt_putlog(get_time(*p->init_time), p->no, "is thinking\n", p->mutex[LOG]);
	}
	return (mt_boolean_load(p->is_running, p->mutex[SIM]) == false);
}
