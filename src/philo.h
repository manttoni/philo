/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:45 by amaula            #+#    #+#             */
/*   Updated: 2024/09/20 15:21:14 by amaula           ###   ########.fr       */
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

# define SUCCESS 1
# define FAILURE 0

typedef struct s_simulation
{
	pthread_mutex_t	*mutex;
	int				value;
}	t_simulation;

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
typedef struct s_time_set
{
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	int				times;
	long			simul_start;
}	t_time_set;

typedef struct s_philo
{
	int				id;
	t_simulation	*simulation;
	int				is_eating;
	t_fork			*left;
	t_fork			*right;
	t_time_set		*time;
	int				last_meal;
	int				times_eaten;
	pthread_mutex_t	*mutex;
}	t_philo;

typedef struct s_session
{
	unsigned int	n;
	pthread_t		*threads;
	t_philo			*philos;
	t_fork			*forks;
}	t_session;

int				simulation_finished(t_simulation *simulation);
void			*watch(void *ptr);
int				validate(int argc, char **argv);
int				min(int a, int b);
void			print_log(t_philo *philo, char *message);
void			monitor_session(t_session *ses);
int				lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
long			timestamp(t_time_set *time);
long			get_ms(void);
int				get_hunger(t_philo *philo);
unsigned int	ft_atoi(char *string);
t_time_set		*time_settings(int argc, char **argv);
void			give_forks(t_session *ses);
void			start_session(t_session *ses);
void			free_session(t_session *ses);
t_session		*create_session(unsigned int n);
void			print_session(t_session *ses);
void			*simulate(void *ptr);

#endif
