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

static void	cleanup_state(t_state *state);
static void	destroy_mutexes(t_state *state, int ph_count);

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
	int		stage;

	stage = cleanup_mode[STAGE];
	if (stage >= STATE)
	{
		if (stage >= SM_INIT)
		{
			if (stage >= MT_INIT)
			{
				if (stage >= THREADS)
				{
					if (stage != END)
						joiner(state, cleanup_mode[PH_COUNT]);
					cleanup_mode[PH_COUNT] = state->init_data[N_PHILO];
				}
				destroy_mutexes(state, cleanup_mode[PH_COUNT]);
			}
			cleanup_state(state);
		}
		free(state);
	}
	if (cleanup_mode[STAGE] == PARSE)
		exit_with_instructions(exit_code);
	exit(exit_code);
}

static void	cleanup_state(t_state *state)
{
	free(state->is_running);
	free(state->dine);
	free(state->init_time);
	free(state->philos);
	free(state->forks);
	free(state->mt_sim);
	free(state->mt_log);
	free(state->mt_dflag);
}

static void	destroy_mutexes(t_state *state, int ph_count)
{
	int		i;

	i = ph_count - 1;
	while (i >= 0)
		pthread_mutex_destroy(&state->forks[i--]);
	if (i-- >= -3)
		pthread_mutex_destroy(state->mt_sim);
	if (i-- >= -3)
		pthread_mutex_destroy(state->mt_log);
	if (i-- >= -3)
		pthread_mutex_destroy(state->mt_dflag);
}

void	exit_with_instructions(const uint8_t exit_code)
{
	size_t		bytes;

	bytes = printf("%s%s%s%s%s%s", \
"Usage: ./philosophers <following arguments>\n", \
"<int: number of philosophers>\n", \
"<int: time to die (ms)>\n", \
"<int: time to eat (ms)>\n", \
"<int: time to sleep (ms)>\n", \
"<(Optional) int: times a philosopher must eat>\n");
	if (bytes < 0)
		exit(EIO);
	exit(exit_code);
}
