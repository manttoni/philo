/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:57 by amaula            #+#    #+#             */
/*   Updated: 2024/09/20 15:36:58 by amaula           ###   ########.fr       */
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

static void	philo_eat(t_philo *philo)
{
	int	start_eating;
	
	if (lock_forks(philo) == 0)
		return ;
	pthread_mutex_lock(philo->mutex);
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->mutex);
	print_log(philo, "is eating");
	start_eating = timestamp(philo->time);
	while (timestamp(philo->time) - start_eating < philo->time->eat)
		usleep(1000);
	unlock_forks(philo);
	philo->last_meal = timestamp(philo->time);
	pthread_mutex_lock(philo->mutex);
	philo->times_eaten++;
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->mutex);
}

static void	philo_sleep(t_philo *philo)
{
	int	start_sleeping;

	print_log(philo, "is sleeping");
	start_sleeping = timestamp(philo->time);
	while (timestamp(philo->time) - start_sleeping < philo->time->sleep)
		usleep(1000);
}

static void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void	*simulate(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (simulation_finished(philo->simulation) == 0)
	{
		philo_eat(philo);
		if (simulation_finished(philo->simulation) == 1)
			break;
		philo_sleep(philo);
		if (simulation_finished(philo->simulation) == 1)
			break;
		philo_think(philo);
	}
	return (NULL);
}
