/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/31 17:14:09 by jvalkama         ###   ########.fr       */
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
	state->philos = malloc(state->data[N_PHILO] * sizeof(t_philo *));
	state->forks = malloc(state->data[N_PHILO] * sizeof(pthread_mutex_t *));
	if (!state->philos)
		clean_exit(state, ENOMEM);
	if (init_simulation(state))
		clean_exit(state, ENOMEM);
}

int	init_simulation(t_state *state)
{
	t_philo				*philo;
	pthread_mutex_t		*fork;
	int					i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		philo = init_philo(state);
		if (!philo)
			return (ERROR);
		if (pthread_mutex_init(fork, NULL))
			return (ERROR);
		state->philos[i] = *philo;
		state->forks[i] = *fork;
		i++;
	}
	return (SUCCESS);
}

t_philo	*init_philo(t_state *state)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_memset(philo, 0, sizeof(*philo));
	return (philo);
}
