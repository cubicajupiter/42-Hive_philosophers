/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:46 by jvalkama          #+#    #+#             */
/*   Updated: 2025/09/12 12:42:06 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <errno.h>

# define N_PHILO		0
# define TO_DIE			1
# define TO_EAT			2
# define TO_SLEEP		3
# define N_EAT			4
# define SUCCESS		0

typedef struct s_states;
{
	int					data[5];
	struct s_fork		**fork_arr;
	struct s_philo		**philo_arr;
	int					exit_code;
}	t_states;

typedef struct s_fork; //DESIGN THESE NEXT!
{
	//jotain siit et tama on kaytosa
	//aina viereiset forkit philolle
	//niit voi trackailla nii et valitsee philon [i], ja forkit [i] ja [i - 1] tai jtn
}	t_fork;

typedef struct s_philo;
{
	bool				is_eating;
	bool				is_sleeping;
	bool				is_thinking;
	bool				is_dead;
}	t_philo;
