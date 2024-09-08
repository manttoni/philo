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

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left->mutex);
	philo->left->is_locked = 1;
	pthread_mutex_lock(philo->right->mutex);
	philo->right->is_locked = 1;
}

void	return_forks(t_philo *philo)
{
	philo->left->is_locked = 0;
	pthread_mutex_unlock(philo->left->mutex);
	philo->right->is_locked = 0;
	pthread_mutex_unlock(philo->right->mutex);
}
