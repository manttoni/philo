#include "philo.h"

void	free_session(t_session *ses)
{
	if (ses->philos)
		free(ses->philos);
	if (ses->threads)
		free(ses->threads);
	if (ses)
		free(ses);
}

t_session	*create_session(char **argv)
{
	t_session *ses;

	ses = malloc(sizeof(t_session));
	if (!ses)
		exit(1);
	memset(ses, 0, sizeof(t_session));
	ses->number_of_philosophers = atoi(argv[1]); // FF
	ses->philos = malloc(ses->number_of_philosophers * sizeof(t_philo));
	ses->threads = malloc(ses->number_of_philosophers * sizeof(pthread_t));
	if (!ses->philos || !ses->threads)
	{
		free_session(ses);
		exit(1);
	}
	memset(ses->philos, 0, ses->number_of_philosophers * sizeof(t_philo));
	return (ses);
}

int	main(int argc, char **argv)
{
	t_session	*ses;

	if (argc < 2)
		return (1);
	ses = create_session(argv);
	free_session(ses);
	return (0);
}
