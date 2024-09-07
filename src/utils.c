#include "philo.h"

unsigned int	ft_atoi(char *string)
{
	unsigned int	ret;

	ret = 0;
	while (*string >= '0' && *string <= '9')
	{
		ret *= 10;
		ret += *string - '0';
		string++;
	}
	if (*string)
	{
		printf(">0\n");
		return (0);
	}
	return (ret);
}
