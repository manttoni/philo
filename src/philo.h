#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				is_locked;
}	t_fork;

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
	t_fork			*left;
	t_fork			*right;
	t_time			*time;
	clock_t			last_meal;
	int				*all_alive;
}	t_philo;

typedef struct s_session
{
	unsigned int	n;
	t_time			*time;
	pthread_t		*threads;
	t_philo			*philos;
	t_fork			*forks;
}	t_session;

void			lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
long			get_ms();
void			take_forks(t_philo *philo);
void			return_forks(t_philo *philo);
int				get_hunger(t_philo *philo);
unsigned int	ft_atoi(char *string);
t_time			*time_settings(int argc, char **argv);
void			give_forks(t_session *ses);
void			start_session(t_session *ses);
void			free_session(t_session *ses);
t_session		*create_session(unsigned int n);
void			print_session(t_session *ses);
void			*sit(void *ptr);

#endif
