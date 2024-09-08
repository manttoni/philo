#include "philo.h"

static void	init_philos(t_session *ses, t_time *time)
{
	unsigned int	i;

	give_forks(ses);
	i = 0;
	while (i < ses->n)
	{
		ses->philos[i].id = i + 1;
		ses->philos[i].time = time;
		ses->philos[i].in_simulation = 1;
		ses->philos[i].last_meal = get_ms();
		ses->philos[i].can_starve = 1;
		ses->philos[i].times_eaten = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_session		*ses;
	unsigned int	n;
	t_time			*time;

	if (argc < 5 || argc > 6)
	{
		printf("<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	time = malloc(sizeof(t_time));
	if (!time)
		return (1);
	n = ft_atoi(argv[1]);
	time->die = ft_atoi(argv[2]);
	time->eat = ft_atoi(argv[3]);
	time->sleep = ft_atoi(argv[4]);
	time->times = -1;
	if (argc == 6)
		time->times = ft_atoi(argv[5]);
	ses = create_session(n);
	if (!ses)
	{
		free(time);
		return (1);
	}
	init_philos(ses, time);
	start_session(ses);
	free_session(ses);
	return (0);
}
