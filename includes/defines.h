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

//STATE CONSTANTS
# define TS				0
# define NO				1
# define VITALS			2

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
# define PARSE			0
# define ST_INIT		1
# define PH_INIT		2
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

enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
};

enum e_mutex_t
{
	SIM,
	LOG,
	OWN_FORK,
	NEXT_FORK,
};

struct s_state
{
	int					init_data[5];
	pthread_t			*threads;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*sim;
	pthread_mutex_t		*log;
	pthread_mutex_t		*dine;
	bool				*is_running;
	bool				*is_dining;
	uint64_t			*init_time;
};

struct s_philo
{
	int					no;
	int					*init_data;
	t_status			vitals;
	uint64_t			*init_time;
	bool				*is_running;
	pthread_mutex_t		*mutex[4];
};

struct s_queue
{
	int					data[3];
	t_queue				*next;
};

#endif
