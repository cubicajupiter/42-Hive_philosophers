
#include "philosophers.h"

void	eat(t_philo *philo)
{
	philo->status = EATING;
	//lock two forks
	write_log(philo);
	usleep(); //times from philo->state->data
	//unlock the forks.
}

void	sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	//lock two forks
	write_log(philo);
	usleep(); //times from philo->state->data
}

void	die(t_philo *philo)
{

}
