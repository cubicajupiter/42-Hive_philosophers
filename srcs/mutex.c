/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:44:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:08:57 by jvalkama         ###   ########.fr       */
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

void	mt_put(t_philo *p, int ts, int msg, pthread_mutex_t *mutex)
{
	int			i;

	pthread_mutex_lock(mutex);
	i = *p->q_tail_idx;
	p->queue[i][0] = ts;
	p->queue[i][1] = p->no;
	p->queue[i][2] = msg;
	*p->q_tail_idx = (i + 1) % 2000;
	pthread_mutex_unlock(mutex);
}

int	mt_lock_forks(pthread_mutex_t *l, pthread_mutex_t *r, t_philo *philo)
{
	pthread_mutex_lock(l);
	pthread_mutex_lock(philo->mutex[PHILO]);
	philo->is_forkmtx[0] = true;
	pthread_mutex_unlock(philo->mutex[PHILO]);
	if (mt_boolean_load(philo->is_running, philo->mutex[SIM]) == false)
		return (DONE);
	mt_put(philo, (int)get_time(*philo->init_time), FORK, philo->mutex[LOG]);
	pthread_mutex_lock(r);
	pthread_mutex_lock(philo->mutex[PHILO]);
	philo->is_forkmtx[1] = true;
	pthread_mutex_unlock(philo->mutex[PHILO]);
	if (mt_boolean_load(philo->is_running, philo->mutex[SIM]) == false)
		return (DONE);
	mt_put(philo, (int)get_time(*philo->init_time), FORK, philo->mutex[LOG]);
	return (DINE);
}

void	mt_unlock_forks(pthread_mutex_t *l, pthread_mutex_t *r)
{
	pthread_mutex_unlock(r);
	pthread_mutex_unlock(l);
}
