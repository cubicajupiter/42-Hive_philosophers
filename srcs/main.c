/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/08 12:50:11 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_states		*state;

	if (ac == 5 || ac == 6)
	{
		state = parse_args(ac, av); //some other call for proceed, parse_args not the pipeline mouth
		initialize(state);
		run_and_log(state); //for example
	}
	else
	{
		ft_putendl_fd("Usage: ./philosophers < 4 or 5 additional arguments: >", 1);
		ft_putendl_fd("< Number: number of philosophers >", 1);
		ft_putendl_fd("< Number: time to die (ms) >", 1);
		ft_putendl_fd("< Number: time to eat (ms) >", 1);
		ft_putendl_fd("< Number: time to sleep (ms) >", 1);
		ft_putendl_fd("< (Optional) Number: times a philosopher must eat >", 1);
	}
	return (0);
}

void	parse_args(int ac, char **av) //insert in struct
{
	t_states	state;
	int			data;
	int			i;

	i = 0;
	while (i < ac)
	{
		data = ft_atoi(av[i]);
		state->data[i] = data;
		i++;
	}
	if (ac == 5)
		state->data[i] = 0;
	return (&state);
}
