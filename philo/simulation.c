/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:57 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 16:36:31 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eat(t_philo *philo)
{
	int	start_eating;

	if (lock_forks(philo) == 0)
	{
		unlock_forks(philo);
		return (0);
	}
	pthread_mutex_lock(philo->mutex);
	philo->last_meal = timestamp(philo->time);
	start_eating = philo->last_meal;
	pthread_mutex_unlock(philo->mutex);
	log_message(philo, "is eating");
	while (timestamp(philo->time) - start_eating < philo->time->eat)
	{
		if (get_status(philo->simulation) == 0)
		{
			unlock_forks(philo);
			return (0);
		}
		usleep(1000);
	}
	unlock_forks(philo);
	pthread_mutex_lock(philo->mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
	return (1);
}

static int	philo_sleep(t_philo *philo)
{
	int	start_sleeping;

	log_message(philo, "is sleeping");
	start_sleeping = timestamp(philo->time);
	while (timestamp(philo->time) - start_sleeping < philo->time->sleep)
	{
		if (get_status(philo->simulation) == 0)
			return (0);
		usleep(1000);
	}
	return (1);
}

void	*simulate(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (get_status(philo->simulation) == 0)
		usleep(100);
	//if (philo->id % 2 == 0)
	//	usleep(1000);
	while (get_status(philo->simulation) == 1)
	{
		if (philo_eat(philo) == 0)
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		log_message(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}
