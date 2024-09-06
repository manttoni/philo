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

int	main(int argc, char **argv)
{
	t_session	*ses;

	if (argc < 5)
		return (1);
	ses = create_session(argv);
	give_forks(ses);
	start_session(ses);
	print_session(ses);
	free_session(ses);
	return (0);
}
