/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:15:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 16:29:21 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	unsigned int	last_meal;
	unsigned int	now;
	unsigned int	time_since_meal;

	pthread_mutex_lock(philo->mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->mutex);
	now = timestamp(philo->time);
	time_since_meal = now - last_meal;
	return (time_since_meal >= philo->time->die);
}

static int	check_death(t_session *ses)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		if (is_dead(philo) == 1)
		{
			print_log(philo, "died");
			set_status(philo->simulation, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	check_satisfaction(t_session *ses)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		pthread_mutex_lock(philo->mutex);
		if (philo->times_eaten < philo->time->times)
		{
			pthread_mutex_unlock(philo->mutex);
			return ;
		}
		pthread_mutex_unlock(philo->mutex);
		i++;
	}
	set_status(philo->simulation, 0);
}

void	*watch(void *ptr)
{
	t_session	*ses;

	ses = (t_session *)ptr;
	while (get_status(ses->philos->simulation) == 0)
		usleep(100);
	while (get_status(ses->philos->simulation) == 1)
	{
		if (check_death(ses) == 0)
			if (ses->philos->time->times > 0)
				check_satisfaction(ses);
	}
	return (NULL);
}
