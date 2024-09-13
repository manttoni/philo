/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:57 by amaula            #+#    #+#             */
/*   Updated: 2024/09/13 12:58:26 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	int	start_eating;

	pthread_mutex_lock(philo->mutex);
	print_log(philo, "is eating");
	start_eating = timestamp(philo->time);
	while (timestamp(philo->time) - start_eating < philo->time->eat)
	{
		if (*philo->all_alive == 0)
		{
			unlock_forks(philo);
			pthread_mutex_unlock(philo->mutex);
			return (0);
		}
		usleep(1000);
	}
	unlock_forks(philo);
	philo->last_meal = timestamp(philo->time);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	int	start_sleeping;

	print_log(philo, "is sleeping");
	start_sleeping = timestamp(philo->time);
	while (timestamp(philo->time) - start_sleeping < philo->time->sleep)
	{
		if (*philo->all_alive == 0)
			return ;
		usleep(1000);
	}
}

void	philo_think(t_philo *philo)
{
	int	min_hunger;

	min_hunger = 0;
	if (*philo->all_alive == 0)
		return ;
	if (get_hunger(philo) < min_hunger || lock_forks(philo) == 0)
	{
		print_log(philo, "is thinking");
		while (get_hunger(philo) < min_hunger || lock_forks(philo) == 0)
		{
			if (*philo->all_alive == 0)
				return ;
			usleep(philo->time->die);
		}
	}
}

void	*watch_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (*philo->all_alive)
	{
		pthread_mutex_lock(philo->mutex);
		if (get_hunger(philo) >= 100 && *philo->all_alive)
		{
			*philo->all_alive = 0;
			print_log(philo, "died");
			break ;
		}
		if (philo->time->times > 0 && philo->times_eaten >= philo->time->times)
			break ;
		pthread_mutex_unlock(philo->mutex);
		usleep(1000);
	}
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*simulate(void *ptr)
{
	t_philo		*philo;
	pthread_t	watch;

	philo = (t_philo *)ptr;
	pthread_create(&watch, NULL, watch_philo, ptr);
	if (*philo->all_alive && philo->id % 2 == 0)
		usleep(1000);
	while (*philo->all_alive)
	{
		philo_think(philo);
		if (*philo->all_alive == 1 && philo_eat(philo))
		{
			if (philo->time->times > 0)
				if (philo->times_eaten >= philo->time->times)
					break ;
			if (*philo->all_alive == 1)
				philo_sleep(philo);
		}
	}
	pthread_join(watch, NULL);
	return (NULL);
}
