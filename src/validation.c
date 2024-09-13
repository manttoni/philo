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
		return (0);
	return (ret);
}

int	validate(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments!\n");
		printf("\t<number_of_philosophers>\n\t<time_to_die>\n");
		printf("\t<time_to_eat>\n\t<time_to_sleep>\n");
		printf("\t[number_of_times_each_philosopher_must_eat] <- optional\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == 0)
		{
			printf("Invalid argument: Give an unsigned non-zero integer!\n");
			return (0);
		}
		i++;
	}
	return (1);
}
