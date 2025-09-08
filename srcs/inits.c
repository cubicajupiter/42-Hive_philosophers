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
void	initialize(t_states state)
{
	t_philo		*philo;
	t_fork		*fork;
	int			i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		philo = malloc(sizeof(t_philo));
		fork = malloc(sizeof(t_fork));
		i++;
	}
}
