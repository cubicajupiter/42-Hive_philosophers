/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:12:50 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 18:33:34 by jvalkama         ###   ########.fr       */
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

static inline void	setup_philos(t_state *state, const int n_philo)
{
	suseconds_t		init_time;
	int				i;

	i = 0;
	init_time = get_time(0);
	while (i < n_philo)
	{
		state->philos[i]->no = i + 1;
		printf("in dispatcher. no set\n");
		printf("in dispatcher. philo no: %d\n", state->philos[i]->no);
		state->philos[i]->vitals = THINKING;
		printf("in dispatcher. vitals set\n");
		state->philos[i]->run_sim = &state->run_sim;
		printf("in dispatcher. run_sim set\n");
		state->philos[i]->init_time = init_time; //move to waiter when queue design implemented
		printf("in dispatcher. init_time set\n");
		state->philos[i]->own_fork = &state->forks[i];
		printf("in dispatcher. own fork set\n");
		state->philos[i]->next_fork = \
&state->forks[(i + 1) % state->init_data[N_PHILO]];
		printf("in dispatcher. next fork set\n");
		i++;
	}
}

static void	waiter(t_state *state)
{
	int				no;
	t_philo			**philos;
	atomic_bool		*run_sim;

	run_sim = &state->run_sim;
	philos = state->philos;
	//state->init_time = get_time(0); will be needed here for queue design
	*run_sim = true;
	while (*run_sim)
	{
		no = 0;
		while (philos[no] && *run_sim)
		{
			if (!philos[no]->vitals)
				*run_sim = false;
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

inline suseconds_t	get_time(const suseconds_t init_time)
{
	struct timeval		tv;
	suseconds_t			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec;
	if (init_time)
	{
		time -= init_time;
		return (time);
	}
	return (time);
}
