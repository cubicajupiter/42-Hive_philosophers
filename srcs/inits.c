/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/20 16:35:16 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize(int ac, char **av, t_state **state)
{
	*state = malloc(sizeof(t_state));
	if (!*state)
		exit(MAL_ERR);
	init_parsed_args(ac, av, *state);
	init_state(*state);
	init_philos(*state);
	init_mutexes(*state);
}

void	init_state(t_state *state)
{
	state->is_running = malloc(sizeof(bool));
	*state->is_running = false;
	state->init_time = malloc(sizeof(uint64_t));
	state->philos = malloc((state->init_data[N_PHILO]) * sizeof(t_philo));
	state->forks = malloc(\
state->init_data[N_PHILO] * sizeof(pthread_mutex_t));
	state->sim = malloc(sizeof(pthread_mutex_t));
	state->log = malloc(sizeof(pthread_mutex_t));
	if (!state->philos || !state->forks || !state->is_running \
|| !state->init_time || !state->sim || !state->log)
		clean_exit(state, MAL_ERR, (int[]){0, ST_INIT});
}

void	init_philos(t_state *state)
{
	int					i;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		state->philos[i].no = i + 1;
		state->philos[i].init_data = state->init_data;
		state->philos[i].vitals = THINKING;
		state->philos[i].is_running = state->is_running;
		state->philos[i].mutex[SIM] = state->sim;
		state->philos[i].mutex[LOG] = state->log;
		state->philos[i].mutex[OWN_FORK] = &state->forks[i];
		state->philos[i].mutex[NEXT_FORK] = \
&state->forks[(i + 1) % state->init_data[N_PHILO]];
		state->philos[i].init_time = state->init_time; //move to waiter when queue design implemented
		i++;
	}
}

void	init_mutexes(t_state *state)
{
	int		i;

	if (pthread_mutex_init(state->sim, NULL))
	 	clean_exit(state, PMI_ERR, (int[]){-1, MT_INIT});
	if (pthread_mutex_init(state->log, NULL))
	 	clean_exit(state, PMI_ERR, (int[]){-2, MT_INIT});
	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		if (pthread_mutex_init(&state->forks[i], NULL))
	 		clean_exit(state, PMI_ERR, (int[]){i, MT_INIT});
		i++;
	}
}
