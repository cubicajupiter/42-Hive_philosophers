/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:13:11 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/18 18:32:26 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <sys/time.h>
# include <pthread.h>
# include <stdatomic.h>

//STATE CONSTANTS
# define N_PHILO		0
# define TTO_DIE		1
# define TTO_EAT		2
# define TTO_SLEEP		3
# define N_EAT			4

//STATUS CODES
# define ERROR			-1
# define SUCCESS		0

typedef struct s_state		t_state;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef struct s_queue		t_queue;

typedef enum e_status		t_status;

enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
};

struct s_state
{
	suseconds_t			init_time;
	int					init_data[5];
	t_philo				**philos;
	pthread_mutex_t		*forks;
	atomic_bool			run_sim;
};

struct s_philo
{
	int					no;
	int					init_data[5];
	t_status			vitals; //could be just local in routine.
	suseconds_t			init_time;
	atomic_bool			*run_sim;
	pthread_mutex_t		*own_fork;
	pthread_mutex_t		*next_fork;
	t_queue				*q_ptr;
};

struct s_queue
{
	pthread_mutex_t		rear_lock;
	int					*rear_ptr;
	int					*front_ptr;
	int					queue[1024][3]; //1024 items with 3 integers each:  12288 bytes  with 4 byte integers
};

#endif
