#include "philo.h"

void	give_forks(t_session *ses)
{
	unsigned int	i;

	i = 0;
	while (i < ses->n)
	{
		ses->forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		ses->forks[i].is_locked = 0;
		pthread_mutex_init(ses->forks[i].mutex, NULL);
		ses->philos[i].right = &ses->forks[i];
		if (i + 1 >= ses->n)
		{
			ses->philos[0].left = &ses->forks[i];
			break ;
		}
		ses->philos[i + 1].left = &ses->forks[i];
		i++;
	}
}

int	lock_forks(t_philo *philo)
{
	if (philo->left->is_locked == 1 || philo->right->is_locked == 1)
		return (0);
	pthread_mutex_lock(philo->left->mutex);
	philo->left->is_locked = 1;
	printf("%ld %d has taken a fork (left)\n", timestamp(philo->time), philo->id);
	pthread_mutex_lock(philo->right->mutex);
	philo->right->is_locked = 1;
	printf("%ld %d has taken a fork (right)\n", timestamp(philo->time), philo->id);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left->mutex);
	philo->left->is_locked = 0;
	pthread_mutex_unlock(philo->right->mutex);
	philo->right->is_locked = 0;
}
