/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:45 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 15:22:07 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

/* Status:
 * 	-1: pthread_create error
 * 	 0: stop simulation
 * 	 1: start normal
 *	 2: wait for threads creation */
typedef struct s_simulation
{
	pthread_mutex_t	*mutex;
	int				status;
}	t_simulation;

/* die = time_to_die
 * eat = time_to_eat
 * sleep = time_to_sleep
 * times = [number_of_times_each_philosopher_must_eat]*/
typedef struct s_time_set
{
	long			simul_start;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	times;
	pthread_mutex_t	*log_mutex;
}	t_time_set;

/* last_meal is the time when it last started eating */
typedef struct s_philo
{
	unsigned int	id;
	unsigned int	last_meal;
	unsigned int	times_eaten;
	t_simulation	*simulation;
	t_time_set		*time;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*mutex;
}	t_philo;

/* n is amount of philosophers in 'philos' array */
typedef struct s_session
{
	unsigned int	n;
	t_philo			*philos;
}	t_session;

void			*watch(void *ptr);
int				validate(int argc, char **argv);
void			print_log(t_philo *philo, char *message);
int				lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
long			timestamp(t_time_set *time);
long			get_ms(void);
unsigned int	parse_string(char *string);
int				run_session(t_session *ses);
t_session		*create_session(unsigned int n, t_time_set *time);
void			*simulate(void *ptr);
void			set_status(t_simulation *sim, int status);
int				get_status(t_simulation *sim);

/* session
 * ->	n	.	.	.	.	.	(number of philos)
 * ->	philos	.	.	.	.	(array that has all philos)
 *  	->	id	.	.	.	.	(between 1 and n)
 * 		->	forks	.	.	.	(left and right forks/mutexes)
 * 		->	simulation	.	.	(one simulation-struct shared between all philos)
 * 			->	status	.	.	(status of the simulation)
 * 		->	time	.	.	.	(one time-struct shared between all philos)
 * 			->	settings	.	(settings defined by user) */

#endif
