/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:40:23 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:42:02 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	cleanup_state(t_state *state);
static void	destroy_mutexes(t_state *state, int ph_count);

int	main(int ac, char **av)
{
	t_state			*state;
	uint8_t			result;

	if (ac == 5 || ac == 6)
	{
		result = initialize(ac, av, &state);
		if (result != SUCCESS)
			return (result);
		result = run_sim(state);
		if (result == SUCCESS)
			clean(state, SUCCESS, (int []){ALL, END});
		return ((int)result);
	}
	else
		display_instructions();
	return (EINVAL);
}

uint8_t	clean(t_state *state, const uint8_t exit_code, int cleanup_mode[2])
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
		display_instructions();
	return (exit_code);
}

static void	cleanup_state(t_state *state)
{
	free(state->is_running);
	free(state->init_time);
	free(state->philos);
	free(state->forks);
	free(state->mt_sim);
	free(state->mt_log);
}

static void	destroy_mutexes(t_state *state, int ph_count)
{
	int		i;

	i = ph_count - 1;
	while (i >= 0)
		pthread_mutex_destroy(&state->forks[i--]);
	if (i-- >= -2)
		pthread_mutex_destroy(state->mt_sim);
	if (i-- >= -2)
		pthread_mutex_destroy(state->mt_log);
}

void	display_instructions(void)
{
	printf("%s%s%s%s%s%s", \
"Usage: ./philosophers <following arguments>\n", \
"<non-negative int: number of philosophers (max. 200)>\n", \
"<non-negative int: time to die (ms)>\n", \
"<non-negative int: time to eat (ms)>\n", \
"<non-negative int: time to sleep (ms)>\n", \
"<(Optional) non-negative int: times a philosopher must eat>\n");
}
