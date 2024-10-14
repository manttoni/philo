/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:52 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 14:59:35 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_session(t_session *ses)
{
	unsigned int	i;

	i = 0;
	if (ses->philos != NULL)
	{
		while (i < ses->n)
		{
			if (ses->philos[i].mutex == NULL)
				break ;
			free(ses->philos[i].mutex);
			i++;
		}
		free(ses->philos->time->log_mutex);
		free(ses->philos->time);
		if (ses->philos->simulation != NULL)
			free(ses->philos->simulation->mutex);
		free(ses->philos->simulation);
		free(ses->philos);
	}
	if (ses->threads)
		free(ses->threads);
	if (ses->forks)
		free(ses->forks);
	free(ses);
}

t_session	*create_session(unsigned int n)
{
	t_session	*ses;

	ses = malloc(sizeof(t_session));
	if (!ses)
		return (NULL);
	ses->n = n;
	ses->philos = malloc(ses->n * sizeof(t_philo));
	ses->threads = malloc(ses->n * sizeof(pthread_t));
	ses->forks = malloc(ses->n * sizeof(pthread_mutex_t));
	if (!ses->philos || !ses->threads || !ses->forks)
	{
		printf("Malloc failed.\n");
		free_session(ses);
		exit(1);
	}
	memset(ses->philos, 0, ses->n * sizeof(t_philo));
	return (ses);
}

static int	create_threads(t_session *ses, pthread_t *watcher)
{
	unsigned int	i;
	t_philo			*philo;
	pthread_t		*thread;

	i = 0;
	while (i < ses->n)
	{
		thread = ses->threads + i;
		philo = ses->philos + i;
		if (pthread_create(thread, NULL, simulate, philo) != 0)
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

static void	join_threads(t_session *ses, pthread_t *watcher, int created)
{
	int	i;

	i = 0;
	while (i < created - 1)
	{
		pthread_join(ses->threads[i], NULL);
		i++;
	}
	if (i < created)
		pthread_join(*watcher, NULL);
	free(watcher);
}

void	start_session(t_session *ses)
{
	pthread_t	*watcher;
	int			created;

	watcher = malloc(sizeof(pthread_t));
	if (watcher == NULL)
		return ;
	created = create_threads(ses, watcher);
	join_threads(ses, watcher, created);
}
