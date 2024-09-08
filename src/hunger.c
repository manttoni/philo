#include "philo.h"

int time_since_meal(t_philo *philo)
{
	clock_t	now;
	double	time_taken;

	now = clock() * 1000;
	time_taken = ((double) (now - philo->last_meal) / CLOCKS_PER_SEC);
	return (time_taken * 1000);
}

int	get_hunger(t_philo *philo)
{
	int	hunger;

	hunger = 100 * time_since_meal(philo) / (philo->time->die);
	return (hunger);
}
