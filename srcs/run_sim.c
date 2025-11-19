/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:50 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/19 16:20:28 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void		dispatcher(t_state *state, pthread_t *threads);
static inline void		setup_philos(t_state *state, const int n_philo);
static void				waiter(t_state *state);
static inline void		joiner(const t_state *state, pthread_t *threads);

void	run_and_log(t_state *state)
{
	pthread_t		threads[state->init_data[N_PHILO]];

	dispatcher(state, threads);
	waiter(state);
	joiner(state, threads);
}

static inline void	dispatcher(t_state *state, pthread_t *threads)
{
	int				i;

	setup_philos(state, state->init_data[N_PHILO]);
	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		pthread_create(&threads[i], NULL, p_dining_routine, state->philos[i]);
		i++;
	}
}

static void	setup_philos(t_state *state, const int n_philo)
{
	uint64_t		init_time;
	int					i;

	i = 0;
	init_time = get_time(0);
	printf("init time: %ld\n", init_time);
	while (i < n_philo)
	{
		state->philos[i]->no = i + 1;
		state->philos[i]->vitals = THINKING;
		state->philos[i]->run_sim = &state->run_sim;
		state->philos[i]->init_time = init_time; //move to waiter when queue design implemented
		state->philos[i]->own_fork = &state->forks[i];
		state->philos[i]->next_fork = \
&state->forks[(i + 1) % state->init_data[N_PHILO]];
		i++;
	}
}

static void	waiter(t_state *state)
{
	int				no;
	t_philo			**philos;

	philos = state->philos;
	//state->init_time = get_time(0); will be needed here for queue design
	state->run_sim = true;
	while (state->run_sim)
	{
		no = 0;
		while (philos[no] && state->run_sim)
		{
			if (!philos[no]->vitals)
				state->run_sim = false;
			no++;
		}
		//put_batch(); figure out logging...
	}
}

static inline void	joiner(const t_state *state, pthread_t *threads)
{
	int			i;
	void		*retval;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		pthread_join(threads[i], &retval);
		i++;
	}
}

uint64_t	get_time(const uint64_t init_time)
{
	struct timeval		tv;
	uint64_t		time;

	gettimeofday(&tv, NULL);
	time = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - init_time);
}
