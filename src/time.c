#include "philo.h"

t_time	*time_settings(int argc, char **argv)
{
	t_time	*time;

	time = malloc(sizeof(t_time));
	if (!time)
		exit (1);
	memset(time, 0, sizeof(t_time));
	time->die = stui(argv[2]);
	time->eat = stui(argv[3]);
	time->sleep = stui(argv[4]);
	if (argc == 6)
		time->times = stui(argv[5]);
	if (time->die * time->eat * time->sleep == 0 || (time->times == 0 && argc == 6))
	{
		free(time);
		return (NULL);
	}
	return (time);
}
