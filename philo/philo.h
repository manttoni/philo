/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:45 by amaula            #+#    #+#             */
/*   Updated: 2024/10/08 18:48:50 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <limits.h>

/* Status:
 * 	-1: error
 * 	 0: stop
 * 	 1: start */
typedef struct s_simulation
{
	pthread_mutex_t	*mutex;
	int				status;
}	t_simulation;

/* n = number_of_philosophers 
 * die = time_to_die
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

typedef struct s_session
{
	unsigned int	n;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_session;

void			*watch(void *ptr);
int				validate(int argc, char **argv);
void			print_log(t_philo *philo, char *message);
int				lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
long			timestamp(t_time_set *time);
long			get_ms(void);
unsigned int	ft_atoi(char *string);
void			give_forks(t_session *ses);
void			start_session(t_session *ses);
void			free_session(t_session *ses);
t_session		*create_session(unsigned int n);
void			*simulate(void *ptr);
void			set_status(t_simulation *sim, int status);
int				get_status(t_simulation *sim);

#endif
