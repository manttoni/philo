#include "philos.h"

void	free_session(t_session *ses)
{
	if (ses->philos)
		free(ses->philos);
	if (ses->threads)
		free(ses->threads);
	if (ses)
		free(ses);
}

t_philo	*create_philos(t_session *ses)
{
	t_philo		*philos;

	philos = malloc(ses->number_of_philosophers * sizeof(t_philo));
	if (!philos)
	{
		free_session(ses);
		exit(1);
	}
	memset(philos, 0, ses->number_of_philosophers * sizeof(t_philo));
	return (philos);
}

pthread_t	*create_threads(t_session *ses)
{
	pthread_t	*threads;

	threads = malloc(ses->number_of_philosophers * sizeof(pthread_t));
	if (!threads)
	{
		free_session(ses);
		exit(1);
	}
	return (threads);
}

t_session	*create_session(int argc, char **argv)
{
	t_session *ses;

	if (argc < 2)
	{
		printf("<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n");
		exit(1);
	}
	ses = malloc(sizeof(t_session));
	if (!ses)
		exit(1);
	memset(ses, 0, sizeof(t_session));
	ses->number_of_philosophers = atoi(argv[1]); // Forbidden function
	ses->philos = create_philos(ses);
	ses->threads = create_threads(ses);
	return (ses);
}

int	main(int argc, char **argv)
{
	t_session	*ses;

	ses = create_session(argc, argv);
	free_session(ses);
	return (0);
}
