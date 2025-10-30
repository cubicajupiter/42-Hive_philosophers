#include "philosophers.h"

void	run_and_log(t_state *state)
{
	get_time(state, &state->init_time);
	loop_sim(state);
}

void	loop_sim(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		pthread_create();
		i++;
	}
}
