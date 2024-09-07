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

void	take_fork(t_philo *philo, int *fork)
{
	if (*fork != 0)
		return ;
	*fork = philo->id;
}

void	return_fork(t_philo *philo, int *fork)
{
	if (*fork != philo->id)
		return ;
	*fork = 0;
}
