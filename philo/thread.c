/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:52 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 13:30:23 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Creates threads until all are created or one fails
 * Starts simulation timer
 * Sets status of simulation based on success or fail
 * Returns number of created threads */
static int	crte_threads(t_session *ses, pthread_t *threads, pthread_t *watcher)
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

/* Joins all created threads */
static void	join_threads(pthread_t *threads, pthread_t *watcher, int created)
{
	int	i;

	i = 0;
	while (i < created - 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	if (i < created)
		pthread_join(*watcher, NULL);
}

/* Creates threads and waits for them to finish
 * Watcher is a thread that continuously checks philo status
 * Return value becomes program exit value */
int	run_session(t_session *ses)
{
	pthread_t		watcher;
	pthread_t		*threads;
	unsigned int	created;

	threads = malloc(ses->n * sizeof(pthread_t));
	if (threads == NULL)
		return (1);
	created = crte_threads(ses, threads, &watcher);
	join_threads(threads, &watcher, created);
	if (get_status(ses->philos->simulation) == -1)
	{
		free(threads);
		printf("pthread_create error\n");
		return (1);
	}
	free(threads);
	return (0);
}
