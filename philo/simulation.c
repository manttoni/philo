/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 15:20:43 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_times_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
}

static int	get_start_eating(t_philo *philo)
{
	int	start_eating;

	pthread_mutex_lock(philo->mutex);
	philo->last_meal = timestamp(philo->time);
	start_eating = philo->last_meal;
	pthread_mutex_unlock(philo->mutex);
	return (start_eating);
}

/* Takes forks as soon as they are available
 * Eats for philo->time->eat ms or until simulation end */
static int	philo_eat(t_philo *philo)
{
	int	start_eating;

	if (lock_forks(philo) != 1)
	{
		unlock_forks(philo);
		return (0);
	}
	start_eating = get_start_eating(philo);
	print_log(philo, "is eating");
	while (timestamp(philo->time) - start_eating < philo->time->eat)
	{
		if (get_status(philo->simulation) != 1)
		{
			unlock_forks(philo);
			return (0);
		}
		usleep(1000);
	}
	unlock_forks(philo);
	increment_times_eaten(philo);
	return (1);
}

/* Sleeps for philo->time->sleep ms or until simulation ends */
static int	philo_sleep(t_philo *philo)
{
	int	start_sleeping;

	print_log(philo, "is sleeping");
	start_sleeping = timestamp(philo->time);
	while (timestamp(philo->time) - start_sleeping < philo->time->sleep)
	{
		if (get_status(philo->simulation) != 1)
			return (0);
		usleep(1000);
	}
	return (1);
}

/* Simulates the dining philosophers
 * Waits until all threads are created
 * 	if succesful, starts simulation
 * 	if not, simulation doesn't start
 * Even id'd philosophers wait 1ms to prevent deadlock
 * 	doesn't work with valgrind. take_forks has solution for that
 * Thinking duration is half of the remaining life after eat and sleep 
 * 	Prevents faster philos from eating the food of the slow ones */
void	*simulate(void *ptr)
{
	t_philo			*philo;
	unsigned int	life;

	philo = (t_philo *)ptr;
	while (get_status(philo->simulation) == 2)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (get_status(philo->simulation) == 1)
	{
		if (philo_eat(philo) == 0)
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		print_log(philo, "is thinking");
		life = philo->time->die - philo->time->eat - philo->time->sleep;
		usleep(life * 500);
	}
	return (NULL);
}
