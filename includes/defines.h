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

typedef struct s_state
{
	int					data[5];
	struct s_fork		**fork_arr;
	struct s_philo		**philo_arr;
}	t_state;

typedef struct s_fork //DESIGN THESE NEXT!
{
	//jotain siit et tama on kaytosa
	//aina viereiset forkit philolle
	//niit voi trackailla nii et valitsee philon [i], ja forkit [i] ja [i - 1] tai jtn
}	t_fork;

typedef struct s_philo
{
	bool				is_eating;
	bool				is_sleeping;
	bool				is_thinking;
	bool				is_dead;
}	t_philo;

#endif
