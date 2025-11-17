
#include "philosophers.h"

void	*p_task_scheduler(void *arg)
{
	t_philo 	*philo;
	int			*data;

	philo = (t_philo *) arg;
	data = philo->init_data;
	while (!philo->run_sim)
		;
	while (philo->run_sim == true)
	{
		if (philo->no % 2 == 0)
			perform(EATING, philo, data[TTO_EAT]);
		else
			perform(SLEEPING, philo, data[TTO_SLEEP]);
		if (TTO_EAT) //runs out)
			philo->status = DEAD;
		if (philo->status = DEAD)
			break ;
		fill_queue();
	}
	return (NULL);
}

static inline void	perform(const t_status act, t_philo *philo, const int tto)
{
	suseconds_t		*timestamp;
	if (act == EATING)
	{
		//lock two forks
	}
	philo->vitals = act;
	timestamp = get_time(philo->init_time);
	fill_queue(philo, timestamp);
	if (act)
		usleep(tto);
	if (act == EATING)
	{
		//unlock forks
	}
}
