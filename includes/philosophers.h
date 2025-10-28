/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/10/28 17:18:02 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "defines.h"

//philosophers.c
void	clean_exit(t_state *state, int exit_code);
int		exit_with_instructions(int exit_code);

//parser.c
void	parse_args(int ac, char **av, t_state *state);

//inits.c
void	init_state(t_state **state);
void	initialize(t_state *state);
int		init_simulation(t_state *state);
t_philo	*init_philo(t_state *state);
t_fork	*init_fork(t_state *state);

#endif
