#include "philo.h"

void	*sit(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	printf("Philosopher %d is sitting\n", philo->id);



	return (NULL);
}
