#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

/* n = number_of_philosophers 
 * die = time_to_die
 * eat = time_to_eat
 * sleep = time_to_sleep
 * times = [number_of_times_each_philosopher_must_eat]*/
typedef struct s_time
{
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	times;
}	t_time;

/* free fork is 0,
 * fork taken is philo->id */
typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_time			*time;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_session
{
	unsigned int	n;
	t_time			*time;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_session;

unsigned int	ft_atoi(char *string);
t_time			*time_settings(int argc, char **argv);
void			give_forks(t_session *ses);
void			take_fork(t_philo *philo, int *fork);
void			return_fork(t_philo *philo, int *fork);
void			start_session(t_session *ses);
void			free_session(t_session *ses);
t_session		*create_session(unsigned int n);
void			print_session(t_session *ses);
void			*sit(void *ptr);

#endif
