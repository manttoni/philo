/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:54:02 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 12:13:46 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_time_set *t)
{
	return (get_ms() - t->simul_start);
}

void	print_log(t_philo *philo, char *message)
{
	if (simulation_finished(philo->simulation) == 0)
		printf("%ld %d %s\n", timestamp(philo->time), philo->id, message);
}

long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
