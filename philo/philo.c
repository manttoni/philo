/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:14 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 14:51:16 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_simulation	*init_simulation(void)
{
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	if (simulation == NULL)
		return (NULL);
	simulation->status = 0;
	simulation->mutex = malloc(sizeof(pthread_mutex_t));
	if (simulation->mutex == NULL)
	{
		free(simulation);
		return (NULL);
	}
	pthread_mutex_init(simulation->mutex, NULL);
	return (simulation);
}

static int	init_philos(t_session *ses, t_time_set *time)
{
	unsigned int	i;
	t_philo			*philo;
	t_simulation	*simulation;

	simulation = init_simulation();
	if (simulation == NULL)
		return (0);
	give_forks(ses);
	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		philo->id = i + 1;
		philo->time = time;
		philo->simulation = simulation;
		philo->mutex = malloc(sizeof(pthread_mutex_t));
		if (!philo->mutex)
			return (0);
		pthread_mutex_init(philo->mutex, NULL);
		i++;
	}
	return (1);
}

t_time_set	*init_time(int argc, char **argv)
{
	t_time_set	*time;

	time = malloc(sizeof(t_time_set));
	if (!time)
		return (NULL);
	time->die = ft_atoi(argv[2]);
	time->eat = ft_atoi(argv[3]);
	time->sleep = ft_atoi(argv[4]);
	time->times = 0;
	if (argc == 6)
		time->times = ft_atoi(argv[5]);
	time->log_mutex = malloc(sizeof(pthread_mutex_t));
	if (!time->log_mutex)
	{
		free(time);
		return (NULL);
	}
	pthread_mutex_init(time->log_mutex, NULL);
	return (time);
}

int	main(int argc, char **argv)
{
	t_session		*ses;
	unsigned int	n;
	t_time_set		*time;

	if (validate(argc, argv) == 0)
		return (1);
	time = init_time(argc, argv);
	if (!time)
		return (1);
	n = ft_atoi(argv[1]);
	ses = create_session(n);
	if (!ses)
	{
		free(time);
		return (1);
	}
	if (init_philos(ses, time) == 1)
		start_session(ses);
	free_session(ses);
	return (0);
}
