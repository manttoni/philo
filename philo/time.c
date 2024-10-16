/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:54:02 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 14:15:49 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_time_set *t)
{
	return (get_ms() - t->simul_start);
}

void	print_log(t_philo *philo, char *message)
{
	lock(philo->time->log_mutex, philo->simulation);
	if (get_status(philo->simulation) == 1)
		printf("%ld %d %s\n", timestamp(philo->time), philo->id, message);
	unlock(philo->time->log_mutex, philo->simulation);
}

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
