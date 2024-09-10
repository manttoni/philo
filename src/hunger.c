#include "philo.h"

int time_since_meal(t_philo *philo)
{
	int		now;
	int		time_taken;

	now = timestamp(philo->time);
	time_taken = (now - philo->last_meal);
	return (time_taken);
}

int	get_hunger(t_philo *philo)
{
	int	hunger;

	hunger = 100 * time_since_meal(philo) / philo->time->die;
	return (hunger);
}
