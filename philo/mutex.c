#include "philo.h"

void	lock(pthread_mutex_t *mutex, t_simulation *simulation)
{
	if (pthread_mutex_lock(mutex) != 0)
		set_status(simulation, -2);
}

void	unlock(pthread_mutex_t *mutex, t_simulation *simulation)
{
	if (pthread_mutex_unlock(mutex) != 0)
		set_status(simulation, -2);
}
