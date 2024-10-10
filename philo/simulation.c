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

int	simulation_finished(t_simulation *sim)
{
	pthread_mutex_lock(sim->mutex);
	if (sim->value == 0)
	{
		pthread_mutex_unlock(sim->mutex);
		return (1);
	}
	pthread_mutex_unlock(sim->mutex);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	int	start_eating;

	if (lock_forks(philo) == 0)
		return (0);
	pthread_mutex_lock(philo->mutex);
	philo->last_meal = timestamp(philo->time);
	start_eating = philo->last_meal;
	pthread_mutex_unlock(philo->mutex);
	print_log(philo, "is eating");
	while (timestamp(philo->time) - start_eating < philo->time->eat)
	{
		if (simulation_finished(philo->simulation) == 1)
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

	print_log(philo, "is sleeping");
	start_sleeping = timestamp(philo->time);
	while (timestamp(philo->time) - start_sleeping < philo->time->sleep)
	{
		if (simulation_finished(philo->simulation) == 1)
		{
			unlock_forks(philo);
			return (0);
		}
		usleep(1000);
	}
	return (1);
}

static void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
	while (get_hunger(philo) < 0)
	{
		if (simulation_finished(philo->simulation) == 1)
		{
			unlock_forks(philo);
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		usleep(1000);
	}
}

void	*simulate(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (simulation_finished(philo->simulation) == 0)
	{
		if (philo_eat(philo) == 0)
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		philo_think(philo);
	}
	return (NULL);
}
