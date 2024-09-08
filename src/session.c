#include "philo.h"

void	free_session(t_session *ses)
{
	if (ses->philos->time)
		free(ses->philos->time);
	if (ses->philos)
		free(ses->philos);
	if (ses->threads)
		free(ses->threads);
	if (ses->forks)
		free(ses->forks);
	if (ses)
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

void	unlock_all(t_session *ses)
{
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		pthread_mutex_unlock(ses->forks[i].mutex);
		i++;
	}
}

void	monitor_session(t_session *ses)
{
	unsigned int	i;
	int				simulate;

	simulate = 1;
	while (simulate)
	{
		simulate = 0;
		i = 0;
		while (i < ses->n)
		{
			if (get_hunger(&ses->philos[i]) >= 100 && ses->philos[i].can_starve == 1)
			{
				printf("%ld Philo %d has died. (Hunger = %d)\t\t\t\t\tDEATH\n", get_ms(), i + 1, get_hunger(&ses->philos[i]));
				simulate = 0;
				unlock_all(ses);
				usleep(10000);
				unlock_all(ses);
				break ;
			}
			if (ses->philos[i].in_simulation && ses->philos[i].times_eaten >= ses->philos->time->times)
			{
				printf("%ld Philo %d has had enough food.\n", get_ms(), i + 1);
				ses->philos[i].in_simulation = 0;
			}
			if (ses->philos[i].in_simulation > 0)
				simulate = 1;
			i++;
		}
	}
	i = 0;
	while (i < ses->n)
	{
		ses->philos[i].in_simulation = 0;
		i++;
	}
}

void	start_session(t_session *ses)
{
	unsigned int i;

	i = 0;
	while (i < ses->n)
	{
		pthread_create(ses->threads + i, NULL, sit, (void *) (ses->philos + i));
		i++;
	}
	monitor_session(ses);
	i = 0;
	while (i < ses->n)
	{
		pthread_join(*(ses->threads + i), NULL);
		i++;
	}
}
