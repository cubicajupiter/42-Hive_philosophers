/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:45 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/19 16:47:59 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	ph_eat(t_philo *philo, const int tto, int *n_eaten);
static inline void	ph_sleep(t_philo *philo, const int tto);
static inline void	log_v(char *vitals, t_philo *philo, const unsigned long ts);
static inline void	log_fork(t_philo *philo, const unsigned long ts);

void	*p_dining_routine(void *arg)
{
	const int		*data;
	t_philo 		*philo;
	int				n_eaten;

	n_eaten = 0;
	philo = (t_philo *) arg;
	data = philo->init_data;
	while (!*philo->run_sim)
		;
	while (*philo->run_sim == true)
	{
		if (philo->no % 2 == 0)
		{
			ph_eat(philo, data[TTO_EAT], &n_eaten);
			ph_sleep(philo, data[TTO_SLEEP]);
		}
		else
		{
			ph_sleep(philo, data[TTO_SLEEP]);
			ph_eat(philo, data[TTO_EAT], &n_eaten);
		}
		philo->vitals = THINKING;
		log_v("is thinking", philo, philo->init_time);
		if (TTO_EAT)
			philo->vitals = DEAD;
		if (philo->vitals == DEAD)
			break ;
	}
	return (NULL);

}

static inline void	ph_eat(t_philo *philo, const int tto, int *n_eaten)
{
	uint64_t			timestamp;

	pthread_mutex_lock(philo->own_fork);
	pthread_mutex_lock(philo->next_fork);
	timestamp = get_time(philo->init_time);
	log_fork(philo, timestamp);
	philo->vitals = EATING;
	log_v("is eating", philo, timestamp);
	usleep(tto);
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->next_fork);
	n_eaten++;
}

static inline void	ph_sleep(t_philo *philo, const int tto)
{
	uint64_t				timestamp;

	timestamp = get_time(philo->init_time);
	philo->vitals = SLEEPING;
	log_v("is sleeping", philo, timestamp);
	usleep(tto);
}

static inline void	log_v(char *vitals, t_philo *philo, const uint64_t ts)
{
	while (*philo->run_sim == true)
	{
		if (!vitals)
		{
			if (printf("%ld %d %s\n", ts, philo->no, "died") == -1)
				write(1, "EIO: printf failed\n", 19);
		}
		else
		{
			if (printf("%ld %d %s\n", ts, philo->no, vitals) == -1)
				write(1, "EIO: printf failed\n", 19);
		}
	}
}

static inline void	log_fork(t_philo *philo, const uint64_t ts)
{
	if (printf("%ld %d has taken a fork\n", ts, philo->no) == -1)
		write(1, "EIO: printf failed\n", 19);
}
