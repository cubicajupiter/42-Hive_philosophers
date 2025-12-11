/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:13:11 by jvalkama          #+#    #+#             */
/*   Updated: 2025/12/01 13:45:54 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>

# define MAX_THREADS	1001

//INIT_DATA CONSTANTS
# define N_PHILO		0
# define TTO_DIE		1
# define TTO_EAT		2
# define TTO_SLEEP		3
# define N_EAT			4

//STATUS CODES
# define PMI_ERR		1
# define PTC_ERR		2
# define MAL_ERR		3
# define SUCCESS		0

//ERROR MODES
# define STATE			0
# define PARSE			1
# define SM_INIT		2
# define MT_INIT		3
# define THREADS		4
# define END			5

//ERROR MODE HANDLES
# define ALL			-1
# define PH_COUNT		0
# define STAGE			1

//SIMULATION FLAGS
# define DINE			0
# define DONE			1
# define DEAD			2

//LOG FLAGS
# define THINKING		0
# define EATING			1
# define FORK			2
# define SLEEPING		3

//QUEUE FLAG
# define EMPTY			0

typedef struct s_state		t_state;
typedef struct s_philo		t_philo;
typedef struct s_qitem		t_qitem;

typedef enum e_status		t_status;
typedef enum e_mutex_t		t_mutex_t;

enum e_mutex_t
{
	SIM,
	LOG,
	L_FORK,
	R_FORK,
};

struct s_state
{
	int					init_data[5];
	pthread_t			*threads;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mt_sim;
	pthread_mutex_t		*mt_log;
	bool				*is_running;
	int64_t				*init_time;
	int					queue[2000][3];
	int					q_tail_idx;
	int					q_head_idx;
};

struct s_philo
{
	int					no;
	int					*init_data;
	int64_t				*init_time;
	int64_t				last_eaten;
	bool				is_full;
	bool				*is_running;
	pthread_mutex_t		*mutex[4];
	bool				is_forkmtx[2];
	int					(*queue)[3];
	int					*q_tail_idx;
};

#endif
