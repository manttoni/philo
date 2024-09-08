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

void	lock_forks(t_philo *philo)
{
	printf("%ld Philo %d tries to take forks\n", get_ms(), philo->id);
	/*if (philo->id % 2 == 0)
	{*/
		pthread_mutex_lock(philo->left->mutex);
		philo->left->is_locked = 1;
		printf("%ld Philo %d has taken a fork. (left)\n", get_ms(), philo->id);
	//}
	pthread_mutex_lock(philo->right->mutex);
	philo->right->is_locked = 1;
	printf("%ld Philo %d has taken a fork. (right)\n", get_ms(), philo->id);
	/*if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left->mutex);
		philo->left->is_locked = 1;
		printf("%ld Philo %d has taken a fork. (left)\n", get_ms(), philo->id);
	}*/
}
void	unlock_forks(t_philo *philo)
{
	/*if (philo->id % 2 == 0)
	{*/
		pthread_mutex_unlock(philo->left->mutex);
		philo->left->is_locked = 0;
	//}
	pthread_mutex_unlock(philo->right->mutex);
	philo->right->is_locked = 0;
	/*if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left->mutex);
		philo->left->is_locked = 0;
	}*/
}
