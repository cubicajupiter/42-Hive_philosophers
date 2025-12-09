/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:50 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:46:49 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static uint8_t		dispatcher(t_state *state);

uint8_t	run_sim(t_state *state)
{
	pthread_t		threads[MAX_THREADS];
	uint8_t			result;

	state->threads = threads;
	result = dispatcher(state);
	if (result != SUCCESS)
		return (result);
	joiner(state, state->init_data[N_PHILO]);
	return (SUCCESS);
}

static uint8_t	dispatcher(t_state *state)
{
	int				i;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		if (pthread_create(&state->threads[i], NULL, dine, &state->philos[i]))
			return (clean(state, PTC_ERR, (int []){i, THREADS}));
		i++;
	}
	if (pthread_create(&state->threads[i], NULL, monitor, state))
		return (clean(state, PTC_ERR, (int []){i, THREADS}));
	return (SUCCESS);
}

void	joiner(const t_state *state, int n_pthreads)
{
	int			i;
	void		*retval;

	i = 0;
	while (i < n_pthreads)
	{
		pthread_join(state->threads[i], &retval);
		i++;
	}
	usleep(150);
	mt_boolean_store(state->is_running, false, state->mt_sim);
	if (n_pthreads == state->init_data[N_PHILO])
		pthread_join(state->threads[i], &retval);
}

int64_t	get_time(const int64_t init_time)
{
	struct timeval		tv;
	int64_t				time;

	gettimeofday(&tv, NULL);
	time = (int64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - init_time);
}
