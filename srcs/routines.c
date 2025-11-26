/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:45 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/25 14:50:45 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dine(void *arg)
{
	t_philo 		*philo;
	int				n_eaten;

	n_eaten = 0;
	philo = (t_philo *)arg;
	printf("no: %d, is_running: %d and its ptr: %p, mutex[SIM] ptr: %p\n", philo->no, *philo->is_running, philo->is_running, philo->mutex[SIM]);
	while (!mt_boolean_load(philo->is_running, philo->mutex[SIM]))
	{
		usleep(50);
	}
	printf("flag given\n");
	if (philo->init_data[N_EAT] == 0)
		return (NULL);
	if (philo->init_data[N_PHILO] == 1)
		return (solo(philo));
	while (mt_boolean_load(philo->is_running, philo->mutex[SIM]))
	{
		if (philo->no % 2 == 1)
			usleep(50);
		ph_eat(philo, philo->init_data[TTO_EAT], &n_eaten);
		if (n_eaten == philo->init_data[N_EAT])
			break ;
		ph_sleep(philo, philo->init_data[TTO_SLEEP]);
		ph_think(philo);
	}
	return (NULL);
}

void	*solo(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	pthread_mutex_lock(philo->mutex[OWN_FORK]);
	printf("%ld %d %s\n", timestamp, philo->no, "picked up a fork\n");
	usleep(philo->init_data[TTO_DIE] * 1000);
	timestamp = get_time(*philo->init_time);
	printf("%ld %d %s\n", timestamp, philo->no, "has died\n");
	return (NULL);
}

void	ph_eat(t_philo *philo, const int tto, int *n_eaten)
{
	uint64_t			timestamp;

	mt_lock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK], philo);
	timestamp = get_time(*philo->init_time);
	philo->vitals = EATING;
	mt_putlog(timestamp, philo->no, "is eating\n", philo->mutex[LOG]);
	usleep(tto * 1000);
	mt_unlock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK]);
	(*n_eaten)++;
}

void	ph_sleep(t_philo *philo, const int tto)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	philo->vitals = SLEEPING;
	mt_putlog(timestamp, philo->no, "is sleeping\n", philo->mutex[LOG]);
	usleep(tto * 1000);
}

void	ph_think(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	philo->vitals = THINKING;
	mt_putlog(timestamp, philo->no, "is thinking\n", philo->mutex[LOG]);
}
