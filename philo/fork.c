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

/* Lock the fork/mutex and print a message */
static void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_log(philo, "has taken a fork");
}

/* Lock both forks in an order depending of philosophers id
 * Even id locks left then right
 * Odd id locks right then left
 * Prevents deadlock when using valgrind */
int	lock_forks(t_philo *philo)
{
	if (philo->left == philo->right)
		return (0);
	if (philo->id % 2 == 0)
		take_fork(philo, philo->left);
	take_fork(philo, philo->right);
	if (philo->id % 2 != 0)
		take_fork(philo, philo->left);
	return (get_status(philo->simulation));
}

/* Unlock both forks */
void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
