/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:14 by amaula            #+#    #+#             */
/*   Updated: 2024/09/20 15:23:33 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_session *ses, t_time_set *time)
{
	unsigned int	i;
	t_philo			*philo;
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	simulation->status = 0;
	simulation->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(simulation->mutex, NULL);
	give_forks(ses);
	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		philo->id = i + 1;
		philo->time = time;
		philo->last_meal = 0;
		philo->times_eaten = 0;
		philo->simulation = simulation;
		philo->mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->mutex, NULL);
		i++;
	}
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
		return (NULL);
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
	init_philos(ses, time);
	start_session(ses);
	free_session(ses);
	return (0);
}
