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

static inline void		check_death(t_state *state, bool *is_running);
static int			philo_dead(t_philo *p, t_state *state);
static inline void		check_log(t_state *state);
static inline void		put_log(int *data);

void	*monitor(void *arg)
{
	t_state			*state;
	bool			is_running;

	state = (t_state *)arg;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->mt_sim);
	is_running = true;
	while (mt_boolean_load(state->is_running, state->mt_sim) == true)
	{
		if (is_running)
			check_death(state, &is_running);
		if (is_running)
			check_log(state);
		usleep(10);
	}
	return (NULL);
}

static inline void	check_death(t_state *state, bool *is_running)
{
	bool		is_full;
	t_philo		*philo;
	int			n_philo;
	int			i;

	n_philo = state->init_data[N_PHILO];
	i = 0;
	while (i < n_philo && *is_running)
	{
		philo = &state->philos[i];
		is_full = mt_boolean_load(&philo->is_full, philo->mutex[PHILO]);
		if (is_full == false && philo_dead(philo, state) == DEAD)
		{
			mt_boolean_store(state->is_running, false, state->mt_sim);
			*is_running = false;
		}
		i++;
	}
}

static int	philo_dead(t_philo *p, t_state *state)
{
	int64_t			last_eaten;

	pthread_mutex_lock(p->mutex[PHILO]);
	last_eaten = p->last_eaten;
	pthread_mutex_unlock(p->mutex[PHILO]);
	if ((int)(get_time(*state->init_time) - last_eaten >= state->init_data[TTO_DIE]))
	{
		if (p->is_forkmtx[1] == true)
			pthread_mutex_unlock(p->mutex[R_FORK]);
		if (p->is_forkmtx[0] == true)
			pthread_mutex_unlock(p->mutex[L_FORK]);
		printf("%ld %d %s\n", get_time(*state->init_time), p->no, "died");
		return (DEAD);
	}
	return (DINE);
}

static inline void	check_log(t_state *state)
{
	int		data;
	int		head;

	head = state->q_head_idx;
	pthread_mutex_lock(state->mt_log);
	data = state->queue[head][1];
	pthread_mutex_unlock(state->mt_log);
	while (data != EMPTY)
	{
		put_log(state->queue[head]);
		state->queue[head][0] = 0;
		state->queue[head][1] = 0;
		state->queue[head][2] = 0;
		head = (state->q_head_idx + 1) % 2000;
		state->q_head_idx = head;
		pthread_mutex_lock(state->mt_log);
		data = state->queue[head][1];
		pthread_mutex_unlock(state->mt_log);
	}
}

static inline void	put_log(int *data)
{
	static char		*logs[4] = \
{"is thinking", "is eating", "has taken a fork", "is sleeping"};

	printf("%d %d %s\n", data[0], data[1], logs[data[2]]);
}
