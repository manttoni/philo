#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

/* n = number_of_philosophers 
 * die = time_to_die
 * eat = time_to_eat
 * sleep = time_to_sleep
 * times = [number_of_times_each_philosopher_must_eat]*/
typedef struct s_time
{
	int			die;
	int			eat;
	int			sleep;
	int			times;
}	t_time;

/* free fork is 0,
 * fork taken is philo->id */
typedef struct s_philo
{
	int		id;
	int		*left;
	int		*right;
	t_time	*time;
}	t_philo;

typedef struct s_session
{
	int			n;
	t_time	*time;
	pthread_t	*threads;
	t_philo		*philos;
	int			*forks;
}	t_session;

unsigned int	stui(char *string);
t_time			*time_settings(int argc, char **argv);
void			give_forks(t_session *ses);
void			take_fork(t_philo *philo, int *fork);
void			return_fork(t_philo *philo, int *fork);
void			start_session(t_session *ses);
void			free_session(t_session *ses);
t_session		*create_session(int argc, char **argv);
void			print_session(t_session *ses);
void			*sit(void *ptr);

#endif
