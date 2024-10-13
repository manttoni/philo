/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:24 by amaula            #+#    #+#             */
/*   Updated: 2024/10/08 18:35:29 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_forks(t_session *ses)
{
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		pthread_mutex_init(&ses->forks[i], NULL);
		ses->philos[i].right = &ses->forks[i];
		if (i + 1 >= ses->n)
		{
			ses->philos[0].left = &ses->forks[i];
			break ;
		}
		ses->philos[i + 1].left = &ses->forks[i];
		i++;
	}
}

int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (get_status(philo->simulation) == 0)
		return (0);
	print_log(philo, "has taken a fork");
	return (1);
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_fork(philo, philo->left) == 0)
		{
			pthread_mutex_unlock(philo->left);
			return (0);
		}
		if (take_fork(philo, philo->right) == 0)
		{
			unlock_forks(philo);
			return (0);
		}
		return (1);
	}
	if (take_fork(philo, philo->right) == 0)
	{
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	if (take_fork(philo, philo->left) == 0)
	{
		unlock_forks(philo);
		return (0);
	}
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
