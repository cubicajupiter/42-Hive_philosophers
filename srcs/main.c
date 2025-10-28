/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 17:57:36 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//TILANNE:
//design the T_FORK struct members next!!!!!!!!!!!!!

int	main(int ac, char **av)
{
	t_state			*state;

	if (ac == 5 || ac == 6)
	{
		init_state(&state);
		parse_args(ac, av, &state);
		initialize(state);
		run_and_log(state);
		clean_exit(state, SUCCESS);
	}
	else
		if (exit_with_instructions(EINVAL));
}

void	clean_exit(t_state *state, int exit_code)
{
	free(); //free everything.
	printf("Philosphers exiting with exit code: %d\n", exit_code);
	exit(exit_code); //exit value
}

int	exit_with_instructions(int exit_code)
{
	size_t		bytes;

	bytes = printf("%s%s%s%s%s%s", \
"Usage: ./philosophers <following arguments>\n", \
"<Integer: number of philosophers>\n", \
"<Integer: time to die (ms)>\n", \
"<Integer: time to eat (ms)>\n", \
"<Integer: time to sleep (ms)>\n", \
"<(Optional) Integer: times a philosopher must eat>\n");
	if (bytes < 0)
		exit(EIO);
	exit(exit_code);
}
