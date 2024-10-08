/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:15:34 by amaula            #+#    #+#             */
/*   Updated: 2024/10/08 14:15:04 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_simulation(t_simulation *simulation)
{
	pthread_mutex_lock(simulation->mutex);
	simulation->value = 0;
	pthread_mutex_unlock(simulation->mutex);
}

static int	check_death(t_session *ses)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		pthread_mutex_lock(philo->mutex);
		if (get_hunger(philo) >= 100 && philo->is_eating == 0)
		{
			finish_simulation(philo->simulation);
			print_log(philo, "died");
			pthread_mutex_unlock(philo->mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->mutex);
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
	finish_simulation(philo->simulation);
}

void	unlock_all_forks(t_session *ses)
{
	unsigned int	i;
	
	i = 0;
	while (i < ses->n)
	{
		unlock_forks(&ses->philos[i]);
		i++;
	}
}

void	*watch(void *ptr)
{
	t_session	*ses;

	ses = (t_session *)ptr;
	while (simulation_finished(ses->philos->simulation) == 0)
	{
		if (check_death(ses) == 0)
			if (ses->philos->time->times > 0)
				check_satisfaction(ses);
	}
	unlock_all_forks(ses);
	return (NULL);
}
