#include "philosophers.h"

void	*proutine(void *state);

// HOW TO CLEAN?
//MAYBE: there needs to be a flag accessible by all that is set to true when somebody dies and detaches,
// each thread would regularly check the flag
// if a thread sees that flag is true, they return, to be joined by main thread.

//

void	run_and_log(t_state *state)
{
	pthread_t		threads[state->data[N_PHILO]];

	get_time(state, &state->init_time);
	thread_launcher(state, threads);
	thread_joiner(state, threads);
	//what else
}

void	thread_launcher(t_state *state, pthread_t *threads)
{
	int				i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		state->philos[i].no = i + 1;
		state->philos[i].state = state;
		state->philos[i].status = THINKING;
		pthread_create(&threads[i], NULL, proutine, &state->philos[i]);
		i++;
	}
}

void	thread_joiner(t_state *state, pthread_t *threads)
{
	int				i;

	i = 0;
	while (i < state->data[N_PHILO])
	{
		pthread_join();
	}
}

void	*proutine(void *arg)
{
	t_philo 	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->no % 2 == 0)
			eat(philo, philo->state->data[TTO_EAT]);
			sleep(philo, philo->state->data[TTO_SLEEP]);
		else
			sleep(philo, philo->state->data[TTO_SLEEP]);
			eat(philo, philo->state->data[TTO_EAT]);
	}
	return (NULL); //RIP
}
