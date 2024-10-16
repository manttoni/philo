#include "philo.h"

static t_simulation	*create_simulation(void)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (sim == NULL)
		return (NULL);
	sim->mutex = malloc(sizeof(pthread_mutex_t));
	if (sim->mutex == NULL)
	{
		free(sim);
		return (NULL);
	}
	if (pthread_mutex_init(sim->mutex, NULL) != 0)
	{
		free(sim);
		free(sim->mutex);
		return (NULL);
	}
	sim->status = 2;
	return (sim);
}

static int	give_shared(t_philo *philos, unsigned int n, t_time_set *time)
{
	unsigned int	i;
	t_simulation	*sim;

	sim = create_simulation();
	if (sim == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		philos[i].time = time;
		philos[i].simulation = sim;
		i++;
	}
	return (1);
}


static int	give_forks(t_philo *philos, unsigned int n)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(n * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (0);
		}
		philos[i].right = &forks[i];
		if (i + 1 >= n)
		{
			philos[0].left = &forks[i];
			break ;
		}
		philos[i + 1].left = &forks[i];
		i++;
	}
	return (1);
}

static int	give_mutexes(t_philo *philos, unsigned int n)
{
	pthread_mutex_t	*mutexes;
	unsigned int	i;

	mutexes = malloc(n * sizeof(pthread_mutex_t));
	if (mutexes == NULL)
		return (0);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			free(mutexes);
			return (0);
		}
		philos[i].mutex = &mutexes[i];
		i++;
	}
	return (1);
}

t_session	*create_session(unsigned int n, t_time_set *time)
{
	t_session	*ses;

	ses = malloc(sizeof(t_session));
	if (ses == NULL)
		return (NULL);
	ses->philos = malloc(n * sizeof(t_philo));
	if (ses->philos == NULL)
	{
		free(ses);
		return (NULL);
	}
	memset(ses->philos, 0, n * sizeof(t_philo));
	ses->n = n;
	if (give_mutexes(ses->philos, n) == 0)
	{
		free(ses->philos);
		free(ses);
		return (NULL);
	}
	if (give_forks(ses->philos, n) == 0)
	{
		free(ses->philos->mutex);
		free(ses->philos);
		free(ses);
		return (NULL);
	}
	if (give_shared(ses->philos, n, time) == 0)
	{
		free(ses->philos->right);
		free(ses->philos->mutex);
		free(ses->philos);
		free(ses);
		return (NULL);
	}
	return (ses);
}
