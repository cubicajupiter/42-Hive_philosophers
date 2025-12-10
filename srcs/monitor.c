/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:43:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 14:17:00 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_dead(t_philo *philo);

void	*monitor(void *arg)
{
	t_state			*state;
	t_philo			*philo;
	int				i;
	bool			is_running;

	state = (t_state *)arg;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->mt_sim);
	is_running = true;
	while (mt_boolean_load(state->is_running, state->mt_sim) == true)
	{
		usleep(500);
		i = 0;
		while (is_running && i < state->init_data[N_PHILO])
		{
			philo = &state->philos[i++];
			if (philo_dead(philo) == DEAD)
			{
				mt_boolean_store(state->is_running, false, state->mt_sim);
				is_running = false;
			}
		}
	}
	return (NULL);
}

static int	philo_dead(t_philo *philo)
{
	int64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	if ((int)(timestamp - philo->last_eaten) >= philo->init_data[TTO_DIE])
	{
		if (philo->is_forkmtx[0] == true)
			pthread_mutex_unlock(philo->mutex[L_FORK]);
		if (philo->is_forkmtx[1] == true)
			pthread_mutex_unlock(philo->mutex[R_FORK]);
		mt_putlog(timestamp, philo->no, "died\n", philo->mutex[LOG]);
		return (DEAD);
	}
	return (DINE);
}

void	*logger(void *arg)
{
	while (true)
	{
//make local copy of next->data in copy_nextdata
//check if copy_nextdata is zeroed or not.
//if zeroed: sleep(a while) ; and continue ; and check again
//else: traverse to next and dequeue (if not zero -> contains values).
//DEQ: log current values.
//DEQ: zero current values in original (not in local copy).
	}
}

/*
alloc memory for each or have a main thread stack buffer + mutex?
stack buffer benefits: NO LOCK CONTENTION
another option: pre-allocated queue.
STACK OVERFLOWS OCCUR AROUND 1MB: 1 million bytes.
Our max is 200 threads, each using 3 ints for a log:
3x4x200 = 2400 bytes.
there could be 2000 times int array[3].
that would be 10 logs per thread with 200 threads.
2000 times 3 int long arrays is 5000x12 = 24.000 bytes. 24kb

How to design the queue itself?
maybe a pre-allocted circular linked list? 
or an int array that loops around via modulo.
a linked list queue could be nice for a dynamic queue where the
consumer can take things while producers put things. however,
mallocs and frees would cause lock contention with a high number
of threads. To avoid lock contention for OS memory operations,  
you could have a pre-allocated linked list/int arr, where the data is
set to 0 after reading it by the consumer. So the producer      
changes an int to a positive value, and the consumer zeroes it.
The producers need a mutex to take turns at the tail pointer.
The tail pointer points to the next empty item after the        
most recently filled item. 

Meanwhile, consumer uses a separate head pointer to traverse
the linked list for as long as the items are filled, logging them
and zeroing them, moving on to next. The consumer needs to
know if the next item is the tail, to avoid overlapping with
producers. The head pointer is separate from tail, so
consumer can log without lock contention with producers.
A Circular linked list would enable us to traverse a certain 
range of items infinitely in a preallocated linked list,
as long as the tail doesn't catch up to the head from behind, 
nor the head access contents in the tail of course.
PROBLEM: monitoring deaths and logging.
So the death monitor and logger cannot be separate, because
the problem would still persist that death and other logs
dont happen efficiently and exactly in chronology.
Both death monitoring and logging need to be in same thread.
That means a philo would monitor its own death so as to
send the death log to the monitor.
 
*/
