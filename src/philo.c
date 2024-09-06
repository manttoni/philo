#include "philo.h"

void	give_forks(t_session *ses)
{
	int	i;

	i = 0;
	while (i < ses->n)
	{
		ses->philos[i].right = ses->forks + i;
		ses->philos[i].id = i + 1;
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

void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	printf("Philosopher %d is sitting\n", philo->id);
	return (NULL);
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

int	main(int argc, char **argv)
{
	t_session	*ses;

	if (argc < 2)
		return (1);
	ses = create_session(argv);
	give_forks(ses);
	start_session(ses);
	print_session(ses);
	free_session(ses);
	return (0);
}
