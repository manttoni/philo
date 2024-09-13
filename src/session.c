/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:52 by amaula            #+#    #+#             */
/*   Updated: 2024/09/13 13:01:26 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_session(t_session *ses)
{
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		free(ses->philos[i].mutex);
		free(ses->forks[i].mutex);
		i++;
	}
	free(ses->philos->time);
	free(ses->philos->all_alive);
	free(ses->philos);
	free(ses->threads);
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
	ses->forks = malloc(ses->n * sizeof(t_fork));
	if (!ses->philos || !ses->threads || !ses->forks)
	{
		free_session(ses);
		exit(1);
	}
	memset(ses->philos, 0, ses->n * sizeof(t_philo));
	return (ses);
}

void	start_session(t_session *ses)
{
	unsigned int	i;
	void			*s;

	s = simulate;
	i = 0;
	ses->philos->time->simul_start = get_ms();
	while (i < ses->n)
	{
		pthread_create(ses->threads + i, NULL, s, (void *)(ses->philos + i));
		i++;
	}
	i = 0;
	while (i < ses->n)
	{
		pthread_join(*(ses->threads + i), NULL);
		i++;
	}
}
