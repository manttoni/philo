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

void	end_session(t_session *ses)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		pthread_mutex_lock(philo->mutex);
		philo->is_alive = 0;
		pthread_mutex_unlock(philo->mutex);
		i++;
	}
}
void	start_session(t_session *ses)
{
	unsigned int i;

	i = 0;
	ses->philos->time->simul_start = get_ms();
	while (i < ses->n)
	{
		pthread_create(ses->threads + i, NULL, simulate, (void *) (ses->philos + i));
		i++;
	}
	i = 0;
	while (i < ses->n)
	{
		if (ses->philos[i].is_alive == 0)
			end_session(ses);
		pthread_join(*(ses->threads + i), NULL);
		i++;
	}
}
