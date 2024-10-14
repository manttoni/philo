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

static int	philo_eat(t_philo *philo)
{
	int	start_eating;

	if (lock_forks(philo) == 0)
	{
		unlock_forks(philo);
		return (0);
	}
	start_eating = get_start_eating(philo);
	print_log(philo, "is eating");
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
	increment_times_eaten(philo);
	return (1);
}

static int	philo_sleep(t_philo *philo)
{
	int	start_sleeping;

	print_log(philo, "is sleeping");
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
	t_philo			*philo;
	unsigned int	life;

	philo = (t_philo *)ptr;
	while (get_status(philo->simulation) == 2)
		usleep(100);
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
