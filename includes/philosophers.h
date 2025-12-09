/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:43:39 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "defines.h"
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

//main.c
uint8_t	clean(t_state *state, const uint8_t exit_code, int cleanup_mode[2]);
void	display_instructions(void);

//parser.c
uint8_t	init_parsed_args(int ac, char **av, t_state *state);

//inits.c
uint8_t	initialize(int ac, char **av, t_state **state);

//run_sim.c
uint8_t	run_sim(t_state *state);
void	joiner(const t_state *state, int n_pthreads);
int64_t	get_time(const int64_t init_time);

//routines.c
void	*dine(void *arg);

//waiter.c
void	*monitor(void *arg);

//mutex.c
void	mt_boolean_store(bool *b, bool value, pthread_mutex_t *mutex);
bool	mt_boolean_load(bool *b, pthread_mutex_t *mutex);
void	mt_putlog(int64_t timestamp, int no, char *log, pthread_mutex_t *mutex);
int		mt_lock_forks(pthread_mutex_t *l, pthread_mutex_t *r, t_philo *philo);
void	mt_unlock_forks(pthread_mutex_t *l, pthread_mutex_t *r);

#endif
