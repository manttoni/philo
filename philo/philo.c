/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:53:14 by amaula            #+#    #+#             */
/*   Updated: 2024/10/14 16:06:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_session(t_session *ses)
{
	free(ses->philos->simulation->mutex);
	free(ses->philos->time->log_mutex);
	free(ses->philos->simulation);
	free(ses->philos->right);
	free(ses->philos->mutex);
	free(ses->philos->time);
	free(ses->philos);
	free(ses);
}

int	give_log_mutex(t_time_set *time)
{
	time->log_mutex = malloc(sizeof(pthread_mutex_t));
	if (time->log_mutex == NULL)
		return (0);
	if (pthread_mutex_init(time->log_mutex, NULL) != 0)
	{
		free(time->log_mutex);
		return (0);
	}
	return (1);
}

void	parse_args(t_time_set *time, int argc, char **argv)
{
	time->die = parse_string(argv[2]);
	time->eat = parse_string(argv[3]);
	time->sleep = parse_string(argv[4]);
	if (argc == 6)
		time->times = parse_string(argv[5]);
	else
		time->times = 0;
}

t_time_set	*create_time(int argc, char **argv)
{
	t_time_set	*time;

	time = malloc(sizeof(t_time_set));
	if (time == NULL)
		return (NULL);
	if (give_log_mutex(time) == 0)
	{
		free(time);
		return (NULL);
	}
	parse_args(time, argc, argv);
	return (time);
}

int	main(int argc, char **argv)
{
	t_session	*ses;
	t_time_set	*time;
	int			ret;

	if (validate(argc, argv) == 0)
		return (1);
	time = create_time(argc, argv);
	if (time == NULL)
		return (1);
	ses = create_session(parse_string(argv[1]), time);
	if (ses == NULL)
	{
		free(time->log_mutex);
		free(time);
		return (1);
	}
	ret = run_session(ses);
	free_session(ses);
	return (ret);
}
