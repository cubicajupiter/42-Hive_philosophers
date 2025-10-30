#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <errno.h>
# include <stdio.h>

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

typedef enum e_status		t_status;

enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DEAD
};

struct s_state
{
	suseconds_t		init_time;
	int				data[5];
	t_fork			**fork_arr;
	t_philo			**philo_arr;
};

struct s_fork
{
	pthread_mutex_t		*mutex;
};

struct s_philo
{
	int				no;
	pthread_t		thread;
	t_status		status;
};

#endif
