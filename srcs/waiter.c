#include "philosophers.h"

// wait for all threads to launch before running sim.

void	*monitor(void *arg)
{
	t_state			*state;
	bool			is_running;

	state = (t_state *)arg;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->sim);
	is_running = true;
	while (mt_boolean_load(state->dining, state->dine)) //FIX: diner's flag considered communication between philos?
	{ //THE MONITOR USED TO CAUSE A DAta RACE, PRESUMABLY, so now alternative approach: diners flag.
		no = 0;
		while (is_running == true)
		{
			printf("philo[%d] vitals: %d\n", no, state->philos[0].vitals);
			if (state->philos[no].vitals == DEAD) //FIX: WE ARE GOING HERE CURRETLY. POSSIBLY A DATA RACE.
			{
				printf("ending too soon?\n");
				mt_boolean_store(state->is_running, false, state->sim);
				is_running = false;
				break ;
			}
			no++;
		}
		usleep(200);
	}
	mt_boolean_store(state->is_running, false, state->sim);
	return (NULL);
}

/*
void	queue(const t_philo *philo, const suseconds_t ts) //NULL terminate queue.
{
	static char		item[];
	static char		**item_queue[1024];

	if (state.run_sim == true)
	{
		get_timestamp();
	}
}

//need to mutex lock the prints as well, since threads shouldnt put anything at the end while batch gets removed from queue.
size_t	merge_batch(int *queue, char **batch, size_t *len)
{
	static const char	*state[4] = {" died", " is eating", " is sleeping", " is thinking"};
	char				*str;
	size_t				i;

	i = 0;
	while (state->run_sim && queue)
	{
		str = queue[TS];
		while (str[j])
			batch[i++] = str[j++];
		str = queue[NO];
		while (str[j])
			batch[i] = str[j++];

		str = state[queue[VITALS]];
		while (str[j])
			batch[i] = str[j++];
	
		//ts + no + state[vitals];
		i++;
		*batch[i] = '\n';
	}
	return (i);
}

void	put_batch(t_state *state)
{
	size_t				len; //len per item: 6 + 1 + len(philo.no) + state_len[vitals]
	char				batch[1000000];

	len = merge_batch(state->q_frontptr, &batch);
	write(1, batch, len);
}

uint64_t	get_time(const uint64_t init_time)
{
	struct timeval		tv;
	uint64_t			time;

	gettimeofday(&tv, NULL);
	time = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time - init_time);
}
*/
