/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:44:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/27 12:01:16 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mt_boolean_store(bool *b, bool value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*b = value;
	pthread_mutex_unlock(mutex);
}

bool	mt_boolean_load(bool *b, pthread_mutex_t *mutex)
{
	bool	boolean;

	pthread_mutex_lock(mutex);
	boolean = *b;
	pthread_mutex_unlock(mutex);
	return (boolean);
}

void	mt_putlog(int64_t timestamp, int no, char *log, pthread_mutex_t *mutex)
{	
	pthread_mutex_lock(mutex);
	printf("%ld %d %s", timestamp, no, log);
	pthread_mutex_unlock(mutex);
}

int	mt_lock_forks(pthread_mutex_t *l, pthread_mutex_t *r, t_philo *philo)
{
	uint64_t			timestamp;

	pthread_mutex_lock(l);
	philo->is_forkmtx[0] = true;
	if (mt_boolean_load(philo->is_running, philo->mutex[SIM]) == false)
		return (DONE);
	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "picked up a fork\n", philo->mutex[LOG]);
	pthread_mutex_lock(r);
	philo->is_forkmtx[1] = true;
	if (mt_boolean_load(philo->is_running, philo->mutex[SIM]) == false)
		return (DONE);
	timestamp = get_time(*philo->init_time);
	mt_putlog(timestamp, philo->no, "picked up a fork\n", philo->mutex[LOG]);
	return (DINE);
}

void	mt_unlock_forks(pthread_mutex_t *l, pthread_mutex_t *r)
{
	pthread_mutex_unlock(l);
	pthread_mutex_unlock(r);
}
