#include "philo.h"

void	set_status(t_simulation *sim, int status)
{
	pthread_mutex_lock(sim->mutex);
	sim->status = status;
	pthread_mutex_unlock(sim->mutex);
}

int	get_status(t_simulation *sim)
{
	int	status;

	pthread_mutex_lock(sim->mutex);
	status = sim->status;
	pthread_mutex_unlock(sim->mutex);
	return (status);
}
