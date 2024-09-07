#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->right);
	printf("Philo %d is eating\n", philo->id);
	usleep(philo->time->eat * 1000);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
	return (1);
}

void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	printf("Philosopher %d is sitting\n", philo->id);
	while (1)
	{
		if (eat(philo))
		{
			printf("Philo %d is sleeping\n", philo->id);
			usleep(philo->time->sleep);
			printf("Philo %d is thinking\n", philo->id);
			usleep(1000000);
		}
	}
	return (NULL);
}
