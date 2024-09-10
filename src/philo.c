#include "philo.h"

static void	init_philos(t_session *ses, t_time_set *time)
{
	unsigned int	i;
	t_philo			*philo;

	give_forks(ses);
	i = 0;
	while (i < ses->n)
	{
		philo = &ses->philos[i];
		philo->id = i + 1;
		philo->time = time;
		philo->last_meal = 0;
		philo->times_eaten = 0;
		philo->is_alive = 1;
		philo->mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->mutex, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_session		*ses;
	unsigned int	n;
	t_time_set		*time;

	if (argc < 5 || argc > 6)
	{
		printf("<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	time = malloc(sizeof(t_time_set));
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
