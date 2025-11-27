/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/27 12:03:27 by jvalkama         ###   ########.fr       */
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
	state->dine = malloc(sizeof(t_dflag));
	*state->dine = DINE;
	state->init_time = malloc(sizeof(uint64_t));
	state->philos = malloc((state->init_data[N_PHILO]) * sizeof(t_philo));
	state->forks = malloc(\
state->init_data[N_PHILO] * sizeof(pthread_mutex_t));
	state->mt_sim = malloc(sizeof(pthread_mutex_t));
	state->mt_log = malloc(sizeof(pthread_mutex_t));
	state->mt_dflag = malloc(sizeof(pthread_mutex_t));
	if (!state->philos || !state->forks || !state->is_running \
|| !state->init_time || !state->mt_sim || !state->mt_log || !state->mt_dflag)
		clean_exit(state, MAL_ERR, (int[]){0, SM_INIT});
}

void	init_philos(t_state *state)
{
	int				i;
	int				n_philo;

	i = 0;
	n_philo = state->init_data[N_PHILO];
	while (i < n_philo)
	{
		state->philos[i].no = i + 1;
		state->philos[i].n_eaten = 0;
		state->philos[i].init_data = state->init_data;
		state->philos[i].is_running = state->is_running;
		state->philos[i].dine = state->dine;
		state->philos[i].mutex[SIM] = state->mt_sim;
		state->philos[i].mutex[LOG] = state->mt_log;
		state->philos[i].mutex[DFLAG] = state->mt_dflag;
		state->philos[i].mutex[OWN_FORK] = &state->forks[i];
		state->philos[i].mutex[NEXT_FORK] = &state->forks[(i + 1) % n_philo];
		state->philos[i].init_time = state->init_time; //move to waiter when queue design implemented
		i++;
	}
}

void	init_mutexes(t_state *state)
{
	int		i;

	if (pthread_mutex_init(state->mt_sim, NULL))
	 	clean_exit(state, PMI_ERR, (int[]){-3, MT_INIT});
	if (pthread_mutex_init(state->mt_log, NULL))
	 	clean_exit(state, PMI_ERR, (int[]){-2, MT_INIT});
	if (pthread_mutex_init(state->mt_dflag, NULL))
	 	clean_exit(state, PMI_ERR, (int[]){-1, MT_INIT});
	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		if (pthread_mutex_init(&state->forks[i], NULL))
	 		clean_exit(state, PMI_ERR, (int[]){i, MT_INIT});
		i++;
	}
}
