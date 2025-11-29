/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:45 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/27 12:08:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		*ph_solo(t_philo *philo);
static int		ph_eat(t_philo *philo, const int tto);
static int		ph_idle(t_philo *philo, const int time_len);

void	*dine(void *arg)
{
	t_philo 		*philo;
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
	while (mt_boolean_load(philo->is_running, philo->mutex[SIM]))
	{
		if (philo->no % 2 == 1 && philo->n_eaten != 0)
			usleep(philo->init_data[TTO_EAT] / 2 * 1000);
		if (ph_eat(philo, philo->init_data[TTO_EAT]) == DONE)
			break ;
		if (philo->n_eaten == philo->init_data[N_EAT])
			break ;
		if (ph_idle(philo, philo->init_data[TTO_SLEEP]) == DONE)
			break ;
		if (ph_idle(philo, 0) == DONE)
			break ;
	}
	return (NULL);
}

static void	*ph_solo(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	pthread_mutex_lock(philo->mutex[OWN_FORK]);
	printf("%ld %d %s\n", timestamp, philo->no, "picked up a fork");
	usleep(philo->init_data[TTO_DIE] * 1000);
	timestamp = get_time(*philo->init_time);
	printf("%ld %d %s\n", timestamp, philo->no, "has died");
	return (NULL);
}

static int	ph_eat(t_philo *philo, const int time_len)
{
	uint64_t			timestamp;

	if (dine_or_done(philo) == DONE)
		return (DONE);
	if (mt_lock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK], philo) == DONE)
		return (DONE);
	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "is eating\n", philo->mutex[LOG]);
	usleep(time_len * 1000);
	mt_unlock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK]);
	philo->is_forkmtx[0] = false;
	philo->is_forkmtx[1] = false;
	philo->n_eaten++;
	philo->last_eaten = get_time(*philo->init_time);
	return (dine_or_done(philo));
}

static int	ph_idle(t_philo *philo, const int time_len)
{
	uint64_t			timestamp;

	if (dine_or_done(philo) == DONE)
		return (DONE);
	if (time_len)
	{
		timestamp = get_time(*philo->init_time);
		mt_putlog(timestamp, philo->no, "is sleeping\n", philo->mutex[LOG]);
		usleep(time_len * 1000);
	}
	else
	{
		timestamp = get_time(*philo->init_time);
		mt_putlog(timestamp, philo->no, "is thinking\n", philo->mutex[LOG]);
	}
	return (dine_or_done(philo));
}

int	dine_or_done(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	if (mt_boolean_load(philo->is_running, philo->mutex[SIM]) == false)
	{
		if (philo->is_forkmtx[0] == true)
			pthread_mutex_unlock(philo->mutex[OWN_FORK]);
		if (philo->is_forkmtx[1] == true)
			pthread_mutex_unlock(philo->mutex[NEXT_FORK]);
		return (DONE);
	}
	if ((int)(timestamp - philo->last_eaten) >= philo->init_data[TTO_DIE])
	{
		mt_diners_flag_store(philo->dine, DEAD + philo->no, philo->mutex[DFLAG]);
		if (philo->is_forkmtx[0] == true)
			pthread_mutex_unlock(philo->mutex[OWN_FORK]);
		if (philo->is_forkmtx[1] == true)
			pthread_mutex_unlock(philo->mutex[NEXT_FORK]);
		//mt_putlog(timestamp, philo, "died\n", philo->mutex[LOG]);
		return (DONE);
	}
	return (DINE);
}
