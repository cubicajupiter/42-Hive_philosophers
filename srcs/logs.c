/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:22:14 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/17 15:58:50 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

inline void	queue(const t_philo *philo, const suseconds_t ts)
{
	static char		**queue[1024];

	if (state.run_sim == true)
	{
		get_timestamp();
	}
}

void	merge_batch(char **batch, size_t *len)
{
	static const char	*status[3] = {"eating", "sleeping", "thinking"};

	while (state->run_sim == true && *batch)
	{
		if (vitals == THINKING || vitals == SLEEPING || vitals == EATING)
			ts + no + "is" + status[vitals];
		else if (!vitals)
		{
			ts + no + "died";
			run_sim == false;
		}
	}
}

void	put_batch(t_state *state)
{
	size_t				len;
	char				*batch;

	len = 0;
	merge_batch(&batch, &len);
	write(1, batch, len);
}

static inline int	log_vitals(t_philo *philo)
{
	size_t			bytes;
	t_status		vitals;
	suseconds_t		ts;

	vitals = philo->vitals;
	get_time(philo->state, &ts);
	ts -= philo->state->init_time;
}

int	log_fork(t_philo *philo)
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
