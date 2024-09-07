#include "philo.h"

int	eat(t_philo *philo)
{
	if (philo->left != 0 || philo->right != 0)
		return (0);
	take_fork(philo, philo->left);
	take_fork(philo, philo->right);
	printf("Philo %d is eating\n", philo->id);
	usleep(philo->time->eat * 1000);
	return_fork(philo, philo->left);
	return_fork(philo, philo->right);
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
