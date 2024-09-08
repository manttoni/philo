#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	printf("%ld Philo %d is sleeping\n", get_ms(), philo->id);
	usleep(philo->time->sleep * 1000);
}

void	eat(t_philo *philo)
{
	if (get_hunger(philo) >= 100)
		return ;
	if (philo->left->is_locked == 0 && philo->right->is_locked == 0)
		lock_forks(philo);
	else
		return ;
	if (get_hunger(philo) >= 100)
		return ;
	printf("%ld Philo %d is eating (hunger = %d)\n", get_ms(), philo->id, get_hunger(philo));
	usleep(philo->time->eat * 1000);
	unlock_forks(philo);
	philo->last_meal = get_ms();
	philo_sleep(philo);
}

void	*sit(void *ptr)
{
	t_philo *philo;
	int		min_hunger;

	min_hunger = 10;
	philo = (t_philo *) ptr;
	while (*philo->all_alive)
	{
		while (get_hunger(philo) < min_hunger)
			usleep(1000);
		if (get_hunger(philo) > min_hunger)
			eat(philo);
		if (get_hunger(philo) >= 100)
		{
			*philo->all_alive = 0;
			printf("%ld Philo %d died (hunger = %d)\n", get_ms(), philo->id, get_hunger(philo));
			break;
		}
	}
	return (NULL);
}
