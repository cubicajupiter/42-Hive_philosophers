/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:22:14 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/30 16:13:19 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	try_write_log(t_state *state, t_philo *philo)
{
	static char		*status[3] = {"eating", "sleeping", "thinking"};
	size_t			bytes;
	t_status		current;
	suseconds_t		ts;

	current = philo->status;
	get_time(state, &ts);
	ts -= state->init_time;
	if (current < 3)
		bytes = printf("%d %d is %s\n", ts, philo->no, status[current]);
	else if (current == FORK)
		bytes = printf("%d %d has taken a fork\n", ts, philo->no);
	else if (current == DEAD)
		bytes = printf("%d %d died\n", ts, philo->no);
	if (bytes == -1)
		clean_exit(state, EIO);
}

void	get_time(t_state *state, suseconds_t *time)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL))
		clean_exit(state, errno);
	*time = tv.tv_usec;
}
