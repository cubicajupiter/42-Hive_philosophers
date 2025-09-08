/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:49 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/08 12:50:09 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// create philos and forks according to N_PHILO (number of philos) in state.
void	initialize(t_states *state)
{
	t_philo		*philo;
	t_fork		*fork;
	int			i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		philo = init_philo(state);
		fork = init_fork(state);
		
		i++;
	}
}

t_philo	*init_philo(t_states state)
{
	philo = malloc(sizeof(t_philo));
}

t_fork	*init_fork(t_states state)
{
	fork = malloc(sizeof(t_fork));
}
