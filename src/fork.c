/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:24 by amaula            #+#    #+#             */
/*   Updated: 2024/09/20 15:18:43 by amaula           ###   ########.fr       */
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

int	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left->mutex);
	if (simulation_finished(philo->simulation))
		return (0);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right->mutex);
	if (simulation_finished(philo->simulation))
		return (0);
	print_log(philo, "has taken a fork");
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);
}
