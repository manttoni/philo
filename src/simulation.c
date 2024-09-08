#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left->mutex);
	pthread_mutex_lock(philo->right->mutex);
	printf("Philo %d is eating\n", philo->id);
	usleep(philo->time->eat * 1000);
	philo->last_meal = clock() * 1000;
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);
}

void	*sit(void *ptr)
{
	t_philo *philo;
	int		hunger;

	philo = (t_philo *) ptr;
	while (*philo->all_alive)
	{
		hunger = get_hunger(philo);
		printf("Philo: %d hunger: %d all_alive: %d\n", philo->id, hunger, *philo->all_alive);
		if (hunger < 100 && !philo->left->is_locked && !philo->right->is_locked)
			eat(philo);
		else if (get_hunger(philo) >= 100)
		{
			*philo->all_alive = 0;
			printf("Philo %d died\n", philo->id);
			break;
		}
		else
		{
			usleep(philo->time->die * 250);
			continue;
		}
		printf("Philo %d is sleeping and thinking\n", philo->id);
		usleep(philo->time->sleep * 1000);
	}
	return (NULL);
}
