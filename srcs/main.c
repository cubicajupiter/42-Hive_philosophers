/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 12:42:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//TILANNE:
//design the T_FORK struct members next!!!!!!!!!!!!!

int	main(int ac, char **av)
{
	t_states		*state;

	if (ac == 5 || ac == 6)
	{
		state = parse_args(ac, av);
		initialize(state);
		run_and_log(state);
		clean_exit(state); //SET EXIT_CODE TO SUCCESS FOR THIS CALL, IF ALL WORKS OUT WITHOUT ERROR.
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
	return (EINVAL);
}

void	clean_exit(t_states *state, int exit_code);
{
	free();
	exit(exit_code); //exit value
}
