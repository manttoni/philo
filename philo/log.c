#include "philo.h"

t_log	*create_log(t_philo *philo, char *message)
{
	t_log	*log;

	log = malloc(sizeof(t_log));
	if (log == NULL)
	{
		set_status(philo->simulation, -1);
		return (NULL);
	}
	log->time = timestamp(philo->time);
	log->id = philo->id;
	log->message = message;
	log->mutex = philo->time->log_mutex;
	return (log);
}

void	*print_log(void *ptr)
{
	t_log	*log;

	log = (t_log *)ptr;
	pthread_mutex_lock(log->mutex);
	printf("%ld %d %s\n", log->time, log->id, log->message);
	pthread_mutex_unlock(log->mutex);
	free(log);
	return (NULL);
}

void	log_message(t_philo *philo, char *message)
{
	t_log		*log;
	pthread_t	thread;

	log = create_log(philo, message);
	if (pthread_create(&thread, NULL, print_log, log) != 0)
	{
		set_status(philo->simulation, -1);
		free(log);
		return ;
	}
	pthread_detach(thread);
}
