/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:22:14 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 16:11:09 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//these might be useful:
//The philos prolly shouldn't do extra work like logging, since their
//time_to is counted by usleep() so additional logging will add extra time
//on top of the time_to so their actions end up being too long

//still, i dont see how a log queue is more performant,
//since using it takes mutex_lock & unlock operations each time from each thread

/*
inline void	queue(const t_philo *philo, const suseconds_t ts)
{
	static char		item[];
	static char		**item_queue[1024];

	if (state.run_sim == true)
	{
		get_timestamp();
	}
}

void	merge_batch(char **batch, size_t *len)
{
	static const char	*status[3] = {"is eating", "is sleeping", "is thinking"};

	while (state->run_sim == true && *batch)
	{
		if (vitals == THINKING || vitals == SLEEPING || vitals == EATING)
			ts + no + status[vitals];
		else if (!vitals)
		{
			ts + no + "died";
			run_sim == false;
		}
		'\n'
	}
}

void	put_batch(t_state *state)
{
	size_t				len;
	char				batch[1000000];

	len = 0;
	merge_batch(&batch, &len);
	write(1, batch, len);
}
*/

static inline void	log_vitals(t_philo *philo)
{
	static const char	*status[3] = {"is eating", "is sleeping", "is thinking"};
	size_t				bytes;
	t_status			vitals;
	suseconds_t			ts;

	vitals = philo->vitals;
	get_time(philo->state, &ts);
	ts -= philo->state->init_time;
	while (state->run_sim == true && *batch)
	{
		if (!vitals)
		{
			printf("%d %d %s\n", ts, no, "died");
			run_sim == false;
		}
		else
			printf("%d %d %s\n", ts, no, status[vitals]);
	}
}

static inline void	log_fork(t_philo *philo)
{
	size_t			bytes;
	suseconds_t		ts;

	bytes = printf("%d %d has taken a fork\n", ts, philo->no);
	if (bytes == -1)
		clean_exit(philo->state, EIO);
}

inline suseconds_t	get_time(const suseconds_t init_time)
{
	struct timeval		tv;
	suseconds_t			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec;
	if (init_time)
	{
		time -= init_time;
		return (time);
	}
	return (time);
}
