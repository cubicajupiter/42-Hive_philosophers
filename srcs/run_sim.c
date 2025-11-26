/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:50 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/20 17:30:48 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		dispatcher(t_state *state);
static void		joiner(const t_state *state);

void	run_sim(t_state *state)
{
	pthread_t		threads[state->init_data[N_PHILO] + 1];

	state->threads = threads;
	dispatcher(state);
	joiner(state);
}

static void	dispatcher(t_state *state)
{
	int				i;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		if (pthread_create(&state->threads[i], NULL, dine, &state->philos[i]))
			clean_exit(state, PTC_ERR, (int[]){i, THREADS});
		i++;
	}
	if (pthread_create(&state->threads[i], NULL, monitor, state))
		clean_exit(state, PTC_ERR, (int[]){i, THREADS});
}

static void	joiner(const t_state *state)
{
	int			i;
	void		*retval;

	i = 0;
	while (i < state->init_data[N_PHILO] + 1)
	{
		pthread_join(state->threads[i], &retval);
		i++;
	}
	*state->dining = DONE;
	pthread_join(state->threads[i], &retval);
}

uint64_t	get_time(const uint64_t init_time)
{
	struct timeval		tv;
	uint64_t			time;

	gettimeofday(&tv, NULL);
	time = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - init_time);
}
