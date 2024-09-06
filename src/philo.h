#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define FREE 0
# define NOT_FREE 1

typedef struct s_philo
{
	int	id;
	int	*left;
	int	*right;
}	t_philo;

/* n = number_of_philosophers 
 * die = time_to_die
 * eat = time_to_eat
 * sleep = time_to_sleep
 * times = [number_of_times_each_philosopher_must_eat]*/
typedef struct s_session
{
	int			n;
	int			die;
	int			eat;
	int			sleep;
	int			times;
	pthread_t	*threads;
	t_philo		*philos;
	int			*forks;
}	t_session;

void		start_session(t_session *ses);
void		free_session(t_session *ses);
t_session	*create_session(char **argv);
void		print_session(t_session *ses);
void		*sit(void *ptr);

#endif
