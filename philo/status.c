/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:15:32 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 14:15:34 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_status(t_simulation *sim, int status)
{
	lock(sim->mutex, sim);
	sim->status = status;
	unlock(sim->mutex, sim);
}

int	get_status(t_simulation *sim)
{
	int	status;

	lock(sim->mutex, sim);
	status = sim->status;
	unlock(sim->mutex, sim);
	return (status);
}
