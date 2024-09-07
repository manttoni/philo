#include "philo.h"

unsigned int	stui(char *string)
{
	unsigned int	ret;

	ret = 0;
	while (*string >= '0' && *string <= '9')
	{
		ret *= 10;
		ret += *string - '0';
		string++;
	}
	if (*string && (*string <= '0' || *string >= '9'))
	{
		printf(">0\n");
		return (0);
	}
	return (ret);
}
