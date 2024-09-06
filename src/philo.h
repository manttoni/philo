#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define FREE 0
# define NOT_FREE 1

typedef struct s_fork
{
	int	status;
}	t_fork;

typedef struct s_philo
{
	t_fork	*left;
	t_fork	*right;
}	t_philo;

typedef struct s_session
{
	int	n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	pthread_t	*threads;
	t_philo		*philos;
	t_fork		*forks;
}	t_session;

#endif
