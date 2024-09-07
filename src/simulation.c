#include "philo.h"

void ts()
{
    time_t now;
    struct tm ts;
    char buf[80];

    // Get current time
    time(&now);

    // Format time, "YYYY-MM-DD HH:MM:SS"
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);

    printf("Current time: %s\n", buf);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	ts();
	printf("Philo %d is eating\n", philo->id);
	usleep(philo->time->eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	while (1)
	{
		if (1)
			eat(philo);
		else
		{
			usleep(1000000);
			continue;
		}
		ts();
		printf("Philo %d is sleeping and thinking\n", philo->id);
		usleep(philo->time->sleep * 1000);
	}
	return (NULL);
}
