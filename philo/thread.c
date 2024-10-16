/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:52 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 16:08:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_session *ses, pthread_t *threads, pthread_t *watcher)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < ses->n)
	{
		philo = ses->philos + i;
		philo->id = i + 1;
		if (pthread_create(&threads[i], NULL, simulate, philo) != 0)
		{
			set_status(ses->philos->simulation, -1);
			return (i);
		}
		i++;
	}
	if (pthread_create(watcher, NULL, watch, ses) != 0)
	{
		set_status(ses->philos->simulation, -1);
		return (i);
	}
	ses->philos->time->simul_start = get_ms();
	set_status(ses->philos->simulation, 1);
	return (i + 1);
}

static int	join_threads(pthread_t *threads, pthread_t *watcher, int created)
{
	int	i;

	i = 0;
	while (i < created - 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (i);
		i++;
	}
	if (i < created && pthread_join(*watcher, NULL) != 0)
			return (i);
	return (i + 1);
}

int	run_session(t_session *ses)
{
	pthread_t		watcher;
	pthread_t		threads[ses->n];
	unsigned int	created;
	unsigned int	joined;

	created = create_threads(ses, threads, &watcher);
	joined = join_threads(threads, &watcher, created);
	if (get_status(ses->philos->simulation) == -1)
	{
		printf("pthread_create error\n");
		return (1);
	}
	if (get_status(ses->philos->simulation) == -2)
	{
		printf("mutex error\n");
		return (2);
	}
	if (joined != created)
	{
		printf("Error joining threads (%d joined)\n", joined);
		return (3);
	}
	return (0);
}
