#include "philo.h"

void	free_session(t_session *ses)
{
	if (ses->philos)
		free(ses->philos);
	if (ses->threads)
		free(ses->threads);
	if (ses->forks)
		free(ses->forks);
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
	ses->n = atoi(argv[1]); // FF
	ses->philos = malloc(ses->n * sizeof(t_philo));
	ses->threads = malloc(ses->n * sizeof(pthread_t));
	ses->forks = malloc(ses->n * sizeof(t_fork));
	if (!ses->philos || !ses->threads || !ses->forks)
	{
		free_session(ses);
		exit(1);
	}
	memset(ses->forks, 0, ses->n * sizeof(t_fork));
	memset(ses->philos, 0, ses->n * sizeof(t_philo));
	return (ses);
}

void	print_session(t_session *ses)
{
	int	i;

	i = 0;
	while (i < ses->n)
	{
		printf("Philosopher %d\n\tLeft fork: %d\n\tRight fork: %d\n\n", i, ses->philos[i].left->status, ses->philos[i].right->status);
		i++;
	}
}

void	give_forks(t_session *ses)
{
	int	i;

	i = 0;
	while (i < ses->n)
	{
		ses->philos[i].right = ses->forks + i;
		if (i + 1 >= ses->n)
		{
			ses->philos[0].left = ses->forks + i;
			break ;
		}
		ses->philos[i + 1].left = ses->forks + i;
		i++;
	}
	print_session(ses);
}

int	main(int argc, char **argv)
{
	t_session	*ses;

	if (argc < 2)
		return (1);
	ses = create_session(argv);
	give_forks(ses);
	ses->philos[5].left->status = 1;
	ses->philos[5].right->status = 1;
	print_session(ses);
	free_session(ses);
	return (0);
}
