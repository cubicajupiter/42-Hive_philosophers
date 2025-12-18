/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:45 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/18 15:58:00 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void		main_routine(t_philo *p);
static void			*ph_solo(t_philo *p);
static int			ph_eat(t_philo *p, const int time_len, int *n_eaten);
static int			ph_idle(t_philo *p, const int time_len, int log);

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
	if (philo->is_forkmtx[1])
		pthread_mutex_unlock(philo->mutex[R_FORK]);
	if (philo->is_forkmtx[0])
		pthread_mutex_unlock(philo->mutex[L_FORK]);
	return (NULL);
}

static inline void	main_routine(t_philo *p)
{
	int		n_eaten;

	n_eaten = 0;
	while (mt_boolean_load(p->is_running, p->mutex[SIM]))
	{
		if (n_eaten == p->init_data[N_EAT])
		{
			mt_boolean_store(&p->is_full, true, p->mutex[PHILO]);
			break ;
		}
		if (!n_eaten && p->no % 2 == 1)
			mt_put(p, \
(int)get_time(*p->init_time), THINKING, p->mutex[LOG]);
		if (n_eaten && p->init_data[N_PHILO] % 2 == 1)
			ph_idle(p, \
(p->init_data[TTO_EAT] * 2000) - (p->init_data[TTO_SLEEP] * 1000), THINKING);
		if (ph_eat(p, p->init_data[TTO_EAT], &n_eaten) == DONE)
			break ;
		if (ph_idle(p, p->init_data[TTO_SLEEP], SLEEPING) == DONE)
			break ;
		if (ph_idle(p, 0, THINKING) == DONE)
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
	pthread_mutex_lock(p->mutex[PHILO]);
	p->last_eaten = get_time(*p->init_time);
	pthread_mutex_unlock(p->mutex[PHILO]);
	mt_put(p, (int)p->last_eaten, EATING, p->mutex[LOG]);
	usleep(time_len * 1000);
	mt_unlock_forks(p->mutex[L_FORK], p->mutex[R_FORK]);
	p->is_forkmtx[0] = false;
	p->is_forkmtx[1] = false;
	(*n_eaten)++;
	return (mt_boolean_load(p->is_running, p->mutex[SIM]) == false);
}

static int	ph_idle(t_philo *p, const int time_len, int log)
{
	if (mt_boolean_load(p->is_running, p->mutex[SIM]) == false)
		return (DONE);
	mt_put(p, (int)get_time(*p->init_time), log, p->mutex[LOG]);
	if (log == SLEEPING)
	{
		usleep(time_len * 1000);
	}
	else if (log == THINKING && time_len)
	{
		if (time_len > 0)
			usleep(time_len / 2);
	}
	return (mt_boolean_load(p->is_running, p->mutex[SIM]) == false);
}
