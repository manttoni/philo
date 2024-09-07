#include "philo.h"

void	free_session(t_session *ses)
{
	if (ses->philos)
		free(ses->philos);
	if (ses->threads)
		free(ses->threads);
	if (ses->forks)
		free(ses->forks);
	if (ses->time)
		free(ses->time);
	if (ses)
		free(ses);
}

t_session	*create_session(int argc, char **argv)
{
	t_session	*ses;
	t_time		*time;

	time = time_settings(argc, argv);
	ses = malloc(sizeof(t_session));
	if (!ses || !time)
	{
		free_session(ses);
		exit(1);
	}
	memset(ses, 0, sizeof(t_session));
	ses->time = time;
	ses->philos = malloc(ses->n * sizeof(t_philo));
	ses->threads = malloc(ses->n * sizeof(pthread_t));
	ses->forks = malloc(ses->n * sizeof(int));
	if (!ses->philos || !ses->threads || !ses->forks)
	{
		free_session(ses);
		exit(1);
	}
	memset(ses->forks, 0, ses->n * sizeof(int));
	memset(ses->philos, 0, ses->n * sizeof(t_philo));
	return (ses);
}

void	print_session(t_session *ses)
{
	int	i;

	i = 0;
	while (i < ses->n)
	{
		printf("Philosopher %d\n\tLeft fork: %d\n\tRight fork: %d\n\n", i, *ses->philos[i].left, *ses->philos[i].right);
		i++;
	}
}

void	start_session(t_session *ses)
{
	int i;

	i = 0;
	while (i < ses->n)
	{
		pthread_create(ses->threads + i, NULL, sit, (void *) (ses->philos + i));
		i++;
	}
	i = 0;
	while (i < ses->n)
	{
		pthread_join(*(ses->threads + i), NULL);
		i++;
	}
}
