#include "philo.h"

int	main(int argc, char **argv)
{
	t_session	*ses;

	if (argc < 5)
	{
		printf("<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	ses = create_session(argc, argv);
	give_forks(ses);
	start_session(ses);
	print_session(ses);
	free_session(ses);
	return (0);
}
