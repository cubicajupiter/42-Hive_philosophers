/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/19 16:20:48 by jvalkama         ###   ########.fr       */
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
void		clean_exit(t_state *state, const uint8_t exit_code, int cleanup_mode[2]);
void		exit_with_instructions(const uint8_t exit_code);
void		joiner(const t_state *state, int n_pthreads);

//parser.c
void		init_parsed_args(int ac, char **av, t_state *state);

//inits.c
void		initialize(int ac, char **av, t_state **state);
void		init_state(t_state *state);
void		init_philos(t_state *state);
void		init_mutexes(t_state *state);

//run_sim.c
void		run_sim(t_state *state);
uint64_t	get_time(const uint64_t init_time); //temp here

//routines.c
void		*dine(void *arg);
t_dflag		dine_or_done(t_philo *philo);

//waiter.c
void		*monitor(void *arg);
void		mt_diners_flag_store(t_dflag *flag, t_dflag value, pthread_mutex_t *mutex);

//mutex.c
void	mt_boolean_store(bool *b, bool value, pthread_mutex_t *mutex);
bool	mt_boolean_load(bool *b, pthread_mutex_t *mutex);
void	mt_putlog(uint64_t timestamp, t_philo *philo, char *log, pthread_mutex_t *mutex);
t_dflag	mt_lock_forks(pthread_mutex_t *own, pthread_mutex_t *next, t_philo *philo);
void	mt_unlock_forks(pthread_mutex_t *own, pthread_mutex_t *next);

#endif
