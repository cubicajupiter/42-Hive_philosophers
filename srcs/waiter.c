/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:43:31 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/27 12:00:04 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	mt_diners_flag_load(int *flag, pthread_mutex_t *mutex);

void	*monitor(void *arg)
{
	t_state			*state;
	int				dflag;
	int				n_philo;
	int				i;

	state = (t_state *)arg;
	n_philo = state->init_data[N_PHILO];
	dflag = DINE;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->mt_sim);
	while (dflag == DINE) //FIX: here just use is_running. SWITCH BACK TO OLD METHOD: LET MONITOR CHECK VITALS (JUST THE TIME). this enables immediate printing of death
	{
		i = 0;
		while (i++ < n_philo)
		{
			philo = state->philos[i];
			if (philo_dead(philo) == DONE)
			{
				mt_boolean_store(state->is_running, false, state->mt_sim); //FIX: Routine would probably best check is_running anywhere that has dead_or_alive now.
				dflag = DEAD;
				//dflag = mt_diners_flag_load(state->dine, state->mt_dflag);
			}
		}
	}
	//mt_boolean_store(state->is_running, false, state->mt_sim);
	//if (dflag != DONE)
	//{
	//	timestamp = get_time(*state->init_time);
	//	mt_putlog(timestamp, dflag - DEAD, "died\n", state->mt_log);
	//}
	return (NULL);
}
/*
static int	mt_diners_flag_load(int *dflag, pthread_mutex_t *mutex)
{
	int		flag;

	pthread_mutex_lock(mutex);
	flag = *dflag;
	pthread_mutex_unlock(mutex);
	return (flag);
}

void	mt_diners_flag_store(int *flag, int value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*flag = value;
	pthread_mutex_unlock(mutex);
}
*/
int	philo_dead(t_philo *philo)
{
	uint64_t			timestamp;

	timestamp = get_time(*philo->init_time);
	if ((int)(timestamp - philo->last_eaten) >= philo->init_data[TTO_DIE])
	{
		if (philo->is_forkmtx[0] == true)
			pthread_mutex_unlock(philo->mutex[OWN_FORK]);
		if (philo->is_forkmtx[1] == true)
			pthread_mutex_unlock(philo->mutex[NEXT_FORK]);
		mt_putlog(timestamp, philo, "died\n", philo->mutex[LOG]);
		return (DEAD);
	}
	return (DINE);
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
