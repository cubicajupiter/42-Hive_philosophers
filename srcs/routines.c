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

//FIX: 2 seems to have died after 200ms of previous time eating, with previous  timetodie at 610? What gives?

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
		return (solo(philo));
	while (mt_boolean_load(philo->is_running, philo->mutex[SIM]))
	{
		if (philo->no % 2 == 1)
			usleep(100);
		if (ph_eat(philo, philo->init_data[TTO_EAT]) == DEAD)
			break ;
		if (philo->n_eaten == philo->init_data[N_EAT])
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

t_dflag	ph_eat(t_philo *philo, const int tto)
{
	uint64_t			timestamp;

	//FIX: IT'S NOT SAVING THE LAST TIME A PHILO ATE?
	//FIX: I think the TTO_DIE is comparing us to ms and is in wrong place also. Should happen when eating actually gets to start.
	timestamp = get_time(*philo->init_time);
	if ((int)(timestamp - philo->last_eaten) >= philo->init_data[TTO_DIE]) //wrong place wrong time ? :D
	{
		mt_diners_flag_store(philo->dine, DEAD, philo->mutex[DFLAG]);
		mt_putlog(timestamp, philo->no, "has died\n", philo->mutex[LOG]);
		return (DEAD);
	}
	mt_lock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK], philo);
	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "is eating\n", philo->mutex[LOG]);
	usleep(tto * 1000);
	mt_unlock_forks(philo->mutex[OWN_FORK], philo->mutex[NEXT_FORK]);
	philo->n_eaten++;
	return (DINE);
}

void	ph_sleep(t_philo *philo, const int tto)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "is sleeping\n", philo->mutex[LOG]);
	usleep(tto * 1000);
}

void	ph_think(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "is thinking\n", philo->mutex[LOG]);
}
