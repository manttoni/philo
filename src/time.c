#include "philo.h"

long	timestamp(t_time_set *t)
{
	return (get_ms() - t->simul_start);
}

void	print_log(t_philo *philo, char *message)
{
	printf("%ld %d %s\n", timestamp(philo->time), philo->id, message);
}

long	get_ms() 
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
