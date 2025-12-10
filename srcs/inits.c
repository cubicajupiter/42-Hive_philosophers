/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:42:07 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static uint8_t	init_state(t_state *state);
static void		init_philos(t_state *state);
static uint8_t	init_mutexes(t_state *state);

uint8_t	initialize(int ac, char **av, t_state **state)
{
	uint8_t		result;

	*state = malloc(sizeof(t_state));
	if (!*state)
		return (MAL_ERR);
	result = init_parsed_args(ac, av, *state);
	if (result != SUCCESS)
		return (result);
	result = init_state(*state);
	if (result != SUCCESS)
		return (result);
	init_philos(*state);
	result = init_mutexes(*state);
	if (result != SUCCESS)
		return (result);
	return (SUCCESS);
}

static uint8_t	init_state(t_state *state)
{
	memset(state->queue, 0, sizeof(state->queue));
	state->is_running = malloc(sizeof(bool));
	*state->is_running = false;
	state->init_time = malloc(sizeof(int64_t));
	state->philos = malloc((state->init_data[N_PHILO]) * sizeof(t_philo));
	state->forks = malloc(state->init_data[N_PHILO] * sizeof(pthread_mutex_t));
	state->mt_sim = malloc(sizeof(pthread_mutex_t));
	state->mt_log = malloc(sizeof(pthread_mutex_t));
	if (!state->philos || !state->forks || !state->is_running \
|| !state->init_time || !state->mt_sim || !state->mt_log)
		return (clean(state, MAL_ERR, (int []){0, SM_INIT}));
	return (SUCCESS);
}

static void	init_philos(t_state *state)
{
	int			i;
	int			n_philo;

	i = 0;
	n_philo = state->init_data[N_PHILO];
	while (i < n_philo)
	{
		init_philomtx(state, i);
		state->philos[i].no = i + 1;
		state->philos[i].init_data = state->init_data;
		state->philos[i].is_running = state->is_running;
		state->philos[i].init_time = state->init_time;
		state->philos[i].last_eaten = 0;
		state->philos[i].is_forkmtx[0] = false;
		state->philos[i].is_forkmtx[1] = false;
		state->philos[i].q_tailptr = state->q_tailptr;
	}
}

static void	init_philomtx(t_state *state, int i)
{
	state->philos[i].mutex[SIM] = state->mt_sim;
	state->philos[i].mutex[LOG] = state->mt_log;
	if (i % 2 == 0)
		state->philos[i].mutex[L_FORK] = &state->forks[i];
	else
		state->philos[i].mutex[L_FORK] = &state->forks[(i + 1) % n_philo];
	if (i % 2 == 0)
		state->philos[i].mutex[R_FORK] = &state->forks[(i + 1) % n_philo];
	else
		state->philos[i].mutex[R_FORK] = &state->forks[i];
}

static uint8_t	init_mutexes(t_state *state)
{
	int		i;

	if (pthread_mutex_init(state->mt_sim, NULL))
		return (clean(state, PMI_ERR, (int []){-2, MT_INIT}));
	if (pthread_mutex_init(state->mt_log, NULL))
		return (clean(state, PMI_ERR, (int []){-1, MT_INIT}));
	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		if (pthread_mutex_init(&state->forks[i], NULL))
			return (clean(state, PMI_ERR, (int []){i, MT_INIT}));
		i++;
	}
	return (SUCCESS);
}
