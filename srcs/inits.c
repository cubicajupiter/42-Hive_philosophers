/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 12:42:05 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// create philos and forks according to N_PHILO (number of philos) in state.
void	initialize(t_states *state)
{
	ft_memset(state, 0, sizeof(*state));
	state->philo_arr = malloc(state->data[N_PHILO] * sizeof(t_philo *));
	if (!state->philo_arr)
	{
		state->exit_code = ENOMEM;
		clean_exit(state);
	}
	if (init_simulation(state))
		clean_exit(state);
}

int	init_simulation(t_states *state)
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
			return (state->exit_code);
		state->philo_arr[i] = philo;
		state->fork_arr[i] = fork;
		i++;
	}
	return (SUCCESS);
}

t_philo	*init_philo(t_states *state)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_memset(philo, 0, sizeof(*philo));
	return (philo);
}

t_fork	*init_fork(t_states *state)
{
	t_fork		*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	ft_memset(fork, 0, sizeof(*fork)); //actually make sure the members should be zeroed as you design the members
	return (fork);
}
