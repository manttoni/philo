#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->right);
	printf("Philo %d is eating\n", philo->id);
	usleep(philo->time->eat * 1000);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
}
void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	printf("Philosopher %d is sitting\n", philo->id);
	while (1)
	{
		if (1)
			eat(philo);
		else
		{
			usleep(1000000);
			continue;
		}
		usleep(philo->time->sleep * 1000);
	}
	return (NULL);
}
