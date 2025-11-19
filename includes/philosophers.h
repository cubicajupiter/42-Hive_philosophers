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
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

//main.c
void				clean_exit(t_state *state, int exit_code);
void				exit_with_instructions(const int exit_code);

//parser.c
void				parse_args(int ac, char **av, t_state **state);

//inits.c
void				init_state(t_state **state);
void				initialize(t_state *state);
int					init_simulation(t_state *state);

//logs.c
int					write_log(t_philo *philo);

//run_sim.c
void				run_and_log(t_state *state);
uint64_t			get_time(const uint64_t init_time); //temp here

//routines.c
void				*p_dining_routine(void *arg);

#endif
