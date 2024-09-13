/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:24 by amaula            #+#    #+#             */
/*   Updated: 2024/09/13 12:53:26 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_forks(t_session *ses)
{
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		ses->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		ses->forks[i].is_locked = 0;
		pthread_mutex_init(ses->forks[i].mutex, NULL);
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

int	lock_fork(t_philo *philo, t_fork *fork)
{
	if (*philo->all_alive == 0)
		return (0);
	pthread_mutex_lock(fork->mutex);
	if (*philo->all_alive == 0)
		return (0);
	fork->is_locked = 1;
	print_log(philo, "has taken a fork");
	return (1);
}

int	lock_forks(t_philo *philo)
{
	if (philo->left == philo->right)
		return (0);
	if (philo->left->is_locked == 1 || philo->right->is_locked == 1)
		return (0);
	if (lock_fork(philo, philo->left) && lock_fork(philo, philo->right))
		return (1);
	unlock_forks(philo);
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	philo->right->is_locked = 0;
	philo->left->is_locked = 0;
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);
}
