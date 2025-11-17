#include "philosophers.h"

static inline void	dispatcher(t_state *state, pthread_t *threads);
static int			waiter(t_state *state, const pthread_t *threads);
static inline void	joiner(t_state *state, pthread_t *threads);

void	run_and_log(t_state *state)
{
	pthread_t		threads[state->init_data[N_PHILO]];

	dispatcher(state, threads);
	waiter(state, threads);
	joiner(state, threads);
}

static inline void	dispatcher(t_state *state, pthread_t *threads)
{
	int				i;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		state->philos[i]->no = i + 1;
		state->philos[i]->vitals = THINKING;
		state->philos[i]->run_sim = &state->run_sim;
		pthread_create(&threads[i], NULL, p_task_scheduler, &state->philos[i]);
		i++;
	}
}

static int	waiter(t_state *state, const pthread_t *threads)
{
	int				no;
	const t_philo	**philos;
	atomic_bool		*run_sim;

	run_sim = &state->run_sim;
	philos = state->philos;
	state->init_time = get_time(0);
	*run_sim = true;
	while (*run_sim)
	{
		no = 0;
		while (philos[no] && *run_sim)
		{
			if (!philos[no]->vitals)
				*run_sim = false;
			no++;
		}
		put_batch();
	}
}

static inline void	joiner(const t_state *state, pthread_t *threads)
{
	int			i;
	void		*retval;

	i = 0;
	while (i < state->init_data[N_PHILO])
	{
		pthread_join(threads[i], &retval);
		i++;
	}
}


