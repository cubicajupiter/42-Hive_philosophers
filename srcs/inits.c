/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 17:57:09 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// create philos and forks according to N_PHILO (number of philos) in state.
void	init_state(t_state **state)
{
	*state = malloc(sizeof(t_state));
}

void	initialize(t_state *state)
{
	state->philo_arr = malloc(state->data[N_PHILO] * sizeof(t_philo *));
	state->fork_arr = malloc(state->data[N_PHILO] * sizeof(t_fork *));
	if (!state->philo_arr || !state->fork_arr)
		clean_exit(state, ENOMEM);
	if (init_simulation(state))
		clean_exit(state, ENOMEM);
}

int	init_simulation(t_state *state)
{
	t_philo		*philo;
	t_fork		*fork;
	int			i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		philo = init_philo(state);
		fork = init_fork(state);
		if (!philo || !fork)
			return (ERROR);
		state->philo_arr[i] = philo;
		state->fork_arr[i] = fork;
		i++;
	}
	return (SUCCESS);
}

t_philo	*init_philo(t_state *state)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_memset(philo, 0, sizeof(*philo));
	return (philo);
}

t_fork	*init_fork(t_state *state)
{
	t_fork		*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	ft_memset(fork, 0, sizeof(*fork)); //actually make sure the members should be zeroed as you design the members
	return (fork);
}
