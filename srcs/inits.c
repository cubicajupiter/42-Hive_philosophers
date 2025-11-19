/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/19 16:25:20 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philo(void);
static pthread_mutex_t	*init_fork(void);

void	init_state(t_state **state)
{
	*state = malloc(sizeof(t_state));
	(*state)->run_sim = false;
}

void	initialize(t_state *state)
{
	state->philos = malloc((state->init_data[N_PHILO] + 1) * sizeof(t_philo *));
	state->forks = malloc(\
state->init_data[N_PHILO] * sizeof(pthread_mutex_t *));
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
	while (i < state->init_data[N_PHILO])
	{
		fork = init_fork();
		philo = init_philo();
		if (!philo || !fork)
			return (ERROR);
		state->philos[i] = philo;
		state->forks[i] = *fork;
		i++;
	}
	state->philos[i] = NULL;
	return (SUCCESS);
}

static t_philo	*init_philo(void)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	return (philo);
}

static pthread_mutex_t	*init_fork(void)
{
	pthread_mutex_t		*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	//fork = memset(fork, 0, sizeof(pthread_mutex_t));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(fork, NULL))
		return (NULL);
	return (fork);
}
