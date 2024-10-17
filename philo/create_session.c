#include "philo.h"

/* Creates the simulation struct and a mutex that protects the status value */
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

/* Gives two pointers to each philosopher
 * time: time settings (eating time, sleeping time etc.)
 * simulation: hold status value (wait, start, stop, error) */
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

/* Creates n forks and gives two to each philosopher
 * The right fork of a philosopher is the left fork of the next one 
 * The right fork of the last philo is the left fork of the first */
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

/* Creates a mutex for each philosopher
 * It is used when accessing 'last_meal' or 'times_eaten' */
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

/* Create data structure that is used in the simulation
 * In case of error, all memory is freed, except for
 * 't_time_set *time' which is allocated in main */
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
