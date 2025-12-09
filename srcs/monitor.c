/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:43:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 14:17:00 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_dead(t_philo *philo);

void	*monitor(void *arg)
{
	t_state			*state;
	t_philo			*philo;
	int				i;
	bool			is_running;

	state = (t_state *)arg;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->mt_sim);
	is_running = true;
	while (mt_boolean_load(state->is_running, state->mt_sim) == true)
	{
		usleep(500);
		i = 0;
		while (is_running && i < state->init_data[N_PHILO])
		{
			philo = &state->philos[i++];
			if (philo_dead(philo) == DEAD)
			{
				mt_boolean_store(state->is_running, false, state->mt_sim);
				is_running = false;
			}
		}
	}
	pthread_mutex_unlock(state->mt_log);
	return (NULL);
}

static int	philo_dead(t_philo *philo)
{
	int64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	if ((int)(timestamp - philo->last_eaten) >= philo->init_data[TTO_DIE])
	{
		if (philo->is_forkmtx[0] == true)
			pthread_mutex_unlock(philo->mutex[L_FORK]);
		if (philo->is_forkmtx[1] == true)
			pthread_mutex_unlock(philo->mutex[R_FORK]);
		mt_putlog(timestamp, philo->no, "died\n", philo->mutex[LOG]);
		return (DEAD);
	}
	return (DINE);
}
