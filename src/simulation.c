#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	print_log(philo, "is eating");
	usleep(philo->time->eat * 1000);
	unlock_forks(philo);
	philo->last_meal = timestamp(philo->time);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->mutex);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	usleep(philo->time->sleep * 1000);
}

int	philo_think(t_philo *philo)
{
	int	min_hunger;

	if (philo->is_alive == 0)
		return (0);
	min_hunger = 0;
	if (get_hunger(philo) < min_hunger || lock_forks(philo) == 0)
	{
		printf("%ld %d is thinking\n", timestamp(philo->time), philo->id);
		while (philo->is_alive && (get_hunger(philo) < min_hunger || lock_forks(philo) == 0))
			usleep(philo->time->die * 10);
	}
	return (philo->is_alive);
}

void	*watch_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->is_alive)
	{
		pthread_mutex_lock(philo->mutex);
		if (get_hunger(philo) >= 100)
		{
			philo->is_alive = 0;
			print_log(philo, "died");
			break ;
		}
		if (philo->times_eaten >= philo->time->times)
			break ;
		pthread_mutex_unlock(philo->mutex);
		usleep(philo->time->die * 10);
	}
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*simulate(void *ptr)
{
	t_philo		*philo;
	pthread_t	watch;

	philo = (t_philo *)ptr;
	pthread_create(&watch, NULL, watch_philo, ptr);
	while (philo->is_alive)
	{
		if (philo_think(philo) == 0)
			break ;
		if (philo_eat(philo))
		{
			if (philo->times_eaten >= philo->time->times)
				break ;
			philo_sleep(philo);
		}
	}
	pthread_join(watch, NULL);
	return (NULL);
}
