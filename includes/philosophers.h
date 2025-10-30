/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/30 16:13:21 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "defines.h"
# include <stdarg.h>
# include <sys/time.h>
# include <pthread.h>

//main.c
void		clean_exit(t_state *state, int exit_code);
int			exit_with_instructions(int exit_code);

//parser.c
void		parse_args(int ac, char **av, t_state *state);

//inits.c
void		init_state(t_state **state);
void		initialize(t_state *state);
int			init_simulation(t_state *state);
t_philo		*init_philo(t_state *state);
t_fork		*init_fork(t_state *state);

//logs.c
int			try_write_log(t_philo *philo);

//run_sim.c
void		run_and_log(t_state *state);

#endif
