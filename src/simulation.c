#include "philo.h"

void	eat(t_philo *philo)
{
	take_forks(philo);
	printf("%ld Philo %d is eating (hunger = %d)\n", get_ms(), philo->id, get_hunger(philo));
	usleep(philo->time->eat * 1000);
	philo->last_meal = get_ms();
	return_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld Philo %d is sleeping\n", get_ms(), philo->id);
	usleep(philo->time->sleep * 1000);
}

void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	while (*philo->all_alive)
	{
		//printf("%ld Philo %d hunger %d\n", get_ms(), philo->id, get_hunger(philo));
		if (get_hunger(philo) > 25 && get_hunger(philo) < 100 && !philo->left->is_locked && !philo->right->is_locked)
		{
			eat(philo);
			philo_sleep(philo);
			continue ;
		}
		else if (get_hunger(philo) >= 100)
		{
			*philo->all_alive = 0;
			printf("%ld Philo %d died (hunger = %d)\n", get_ms(), philo->id, get_hunger(philo));
			break;
		}
		else
			usleep(100);
	}
	return (NULL);
}
