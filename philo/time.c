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

/* Current time since start of simulation in ms */
long	timestamp(t_time_set *t)
{
	return (get_ms() - t->simul_start);
}

/* If simulation is running normally, prints the message 
 * timestamp_in_ms philo_id message */
void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->time->log_mutex);
	if (get_status(philo->simulation) == 1)
		printf("%ld %d %s\n", timestamp(philo->time), philo->id, message);
	pthread_mutex_unlock(philo->time->log_mutex);
}

/* Gets current time in ms */
long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
