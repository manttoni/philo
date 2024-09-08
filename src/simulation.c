#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	printf("%ld Philo %d is sleeping\n", get_ms(), philo->id);
	usleep(philo->time->sleep * 1000);
}

void	eat(t_philo *philo)
{
	//if (philo->id % 2 == 0)
	//	usleep(1000);
	if (philo->left->is_locked == 0 && philo->right->is_locked == 0)
		lock_forks(philo);
	else
		return ;
	if (philo->in_simulation == 0)
		return ;
	printf("%ld Philo %d is eating (hunger = %d)\n", get_ms(), philo->id, get_hunger(philo));
	philo->can_starve = 0;
	usleep(philo->time->eat * 1000);
	unlock_forks(philo);
	philo->last_meal = get_ms();
	philo->can_starve = 1;
	philo->times_eaten++;
	if (philo->in_simulation)
		philo_sleep(philo);
}

void	*sit(void *ptr)
{
	t_philo			*philo;
	int				min_hunger;

	min_hunger = 0;
	philo = (t_philo *) ptr;
	while (philo->in_simulation > 0)
	{
		eat(philo);
		while (get_hunger(philo) < min_hunger)
			usleep(1000);
	}
	printf("%ld Philo %d is out\n", get_ms(), philo->id);
	philo->can_starve = 0;
	return (NULL);
}
