/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:13:11 by jvalkama          #+#    #+#             */
/*   Updated: 2025/11/25 13:45:15 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>

//INIT_DATA CONSTANTS
# define N_PHILO		0
# define TTO_DIE		1
# define TTO_EAT		2
# define TTO_SLEEP		3
# define N_EAT			4

//STATUS CODES
# define ERROR			1
# define PMI_ERR		2
# define PTC_ERR		3
# define MAL_ERR		4
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

typedef struct s_state		t_state;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
typedef struct s_queue		t_queue;

typedef enum e_status		t_status;
typedef enum e_mutex_t		t_mutex_t;
typedef enum e_dflag		t_dflag;

enum e_mutex_t
{
	SIM,
	LOG,
	DFLAG,
	OWN_FORK,
	NEXT_FORK,
};

enum e_dflag
{
	DINE = 1,
	DONE,
	DEAD,
};

struct s_state
{
	int					init_data[5];
	pthread_t			*threads;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mt_sim;
	pthread_mutex_t		*mt_log;
	pthread_mutex_t		*mt_dflag;
	bool				*is_running;
	t_dflag				*dine;
	uint64_t			*init_time;
};

struct s_philo
{
	int					no;
	int					n_eaten;
	int					*init_data;
	uint64_t			*init_time;
	uint64_t			last_eaten;
	bool				*is_running;
	t_dflag				*dine;
	pthread_mutex_t		*mutex[5];
};

struct s_queue
{
	int					data[3];
	t_queue				*next;
};

#endif
