/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:44:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/25 14:30:31 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mt_boolean_store(bool *b, bool value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("is waiter in mt_boolean_store - did it mutex lock?\n");
	*b = value;
	pthread_mutex_unlock(mutex);
	printf("mutex unlocked\n");
}

bool	mt_boolean_load(bool *b, pthread_mutex_t *mutex)
{
	bool	boolean;

	pthread_mutex_lock(mutex);
	boolean = *b;
	pthread_mutex_unlock(mutex);
	return (boolean);
}

void	mt_putlog(uint64_t timestamp, int no, char *log, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%ld %d %s", timestamp, no, log);
	pthread_mutex_unlock(mutex);
}

void	mt_lock_forks(pthread_mutex_t *own, pthread_mutex_t *next, t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	pthread_mutex_lock(own);
	mt_putlog(timestamp, philo->no, "picked up a fork", philo->mutex[LOG]);
	pthread_mutex_lock(next);
	mt_putlog(timestamp, philo->no, "picked up a fork", philo->mutex[LOG]);
}

void	mt_unlock_forks(pthread_mutex_t *own, pthread_mutex_t *next)
{
	pthread_mutex_unlock(own);
	pthread_mutex_unlock(next);
}
