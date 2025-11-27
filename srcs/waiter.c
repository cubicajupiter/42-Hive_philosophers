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

static t_dflag	mt_diners_flag_load(t_dflag *flag, pthread_mutex_t *mutex);

void	*monitor(void *arg)
{
	t_state			*state;

	state = (t_state *)arg;
	*state->init_time = get_time(0);
	mt_boolean_store(state->is_running, true, state->mt_sim);
	while (DINE == mt_diners_flag_load(state->dine, state->mt_dflag))
	{
		usleep(50);
	}
	mt_boolean_store(state->is_running, false, state->mt_sim);
	return (NULL);
}

static t_dflag	mt_diners_flag_load(t_dflag *dflag, pthread_mutex_t *mutex)
{
	t_dflag		flag;

	pthread_mutex_lock(mutex);
	flag = *dflag;
	pthread_mutex_unlock(mutex);
	return (flag);
}

void	mt_diners_flag_store(t_dflag *flag, t_dflag value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*flag = value;
	pthread_mutex_unlock(mutex);
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
