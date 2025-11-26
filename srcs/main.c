/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 16:11:23 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_with_instructions(const int exit_code);

int	main(int ac, char **av)
{
	t_state			*state;

	if (ac == 5 || ac == 6)
	{
		initialize(ac, av, &state);
		run_sim(state);
		clean_exit(state, SUCCESS, (int[]){ALL, END});
	}
	else
		exit_with_instructions(EINVAL);
}

void	clean_exit(t_state *state, const uint8_t exit_code, int cleanup_mode[2])
{
	if (cleanup_mode[STAGE] >= PARSE)
	{
		if (cleanup_mode[STAGE] >= ST_INIT)
		{
			if (cleanup_mode[STAGE] >= PH_INIT)
			{
				if (cleanup_mode[STAGE] >= MT_INIT)
				{
					if (cleanup_mode[STAGE] >= THREADS)
					{
						if (cleanup_mode[STAGE] == END)
							; //need two values for number of threads and philos to free. but at end it's obv N_PHILO
					}
				}
			}
		}
	}


	free(state); //separately free everything in state that was mallocd. 
	//free in reverse order. init_data freed second last. state freed last.
	//need state->init_data[N_PHILOS] (or cleanup_mode[COUNT]) for counting how many philos&forks to free.
	exit(exit_code); //exit value
}

void	exit_with_instructions(const int exit_code)
{
	size_t		bytes;

	bytes = printf("%s%s%s%s%s%s", \
"Usage: ./philosophers <following arguments>\n", \
"<Unsigned int: number of philosophers>\n", \
"<Unsigned int: time to die (ms)>\n", \
"<Unsigned int: time to eat (ms)>\n", \
"<Unsigned int: time to sleep (ms)>\n", \
"<(Optional) Unsigned int: times a philosopher must eat>\n");
	if (bytes < 0)
		exit(EIO);
	exit(exit_code);
}
