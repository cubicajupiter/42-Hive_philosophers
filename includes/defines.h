#ifndef DEFINES_H
# define DEFINES_H

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
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
};

struct s_state
{
	const suseconds_t	init_time;
	const int			init_data[5];
	t_philo				**philos;
	pthread_mutex_t		*forks;
	atomic_bool			run_sim;
};

struct s_philo
{
	int					no;
	int					init_data[5];
	int					n_eaten;
	t_status			vitals;
	atomic_bool			*run_sim;
};

#endif
