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
static int			philo_dead(t_philo *p);
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
	}
	return (NULL);
}

static inline void	check_death(t_state *state, bool *is_running)
{
	t_philo		*philo;
	int			n_philo;
	int			i;

	n_philo = state->init_data[N_PHILO];
	i = 0;
	while (i < n_philo && *is_running)
	{
		philo = &state->philos[i];
		if (philo->is_full == false && philo_dead(philo) == DEAD)
		{
			mt_boolean_store(state->is_running, false, state->mt_sim);
			*is_running = false;
		}
		i++;
	}
}

static int	philo_dead(t_philo *p)
{
	int64_t			timestamp;

	timestamp = get_time(*p->init_time);
	if ((int)(timestamp - p->last_eaten) >= p->init_data[TTO_DIE])
	{
		if (p->is_forkmtx[0] == true)
			pthread_mutex_unlock(p->mutex[L_FORK]);
		if (p->is_forkmtx[1] == true)
			pthread_mutex_unlock(p->mutex[R_FORK]);
		printf("%ld %d %s\n", timestamp, p->no, "died");
		return (DEAD);
	}
	return (DINE);
}

static inline void	check_log(t_state *state)
{
	int		data;
	int		head;

	head = state->q_head_idx;
	data = state->queue[head][1];
	while (data != EMPTY)
	{
		put_log(state->queue[head]);
		state->queue[head][0] = 0;
		state->queue[head][1] = 0;
		state->queue[head][2] = 0;
		head = (state->q_head_idx + 1) % 2000;
		state->q_head_idx = head;
		data = state->queue[head][1];
	}
}

static inline void	put_log(int *data)
{
	static char		*logs[4] = \
{"is thinking", "is eating", "has taken a fork", "is sleeping"};

	printf("%d %d %s\n", data[0], data[1], logs[data[2]]);
}
