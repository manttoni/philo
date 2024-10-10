/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:54:10 by amaula            #+#    #+#             */
/*   Updated: 2024/10/10 12:02:33 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(char *string)
{
	unsigned long	ret;

	ret = 0;
	while (*string >= '0' && *string <= '9')
	{
		ret *= 10;
		ret += *string - '0';
		string++;
		if (ret > INT_MAX)
		{
			printf("Overflow error");
			return (0);
		}
	}
	if (*string)
	{
		printf("Value error");
		return (0);
	}
	return ((int)ret);
}

static int	check_memory(int n)
{
	size_t	needed_memory;

	needed_memory = sizeof(t_philo);
	needed_memory += sizeof(pthread_t) + sizeof(pthread_mutex_t);
	needed_memory *= n;
	if (needed_memory > 1000000000)
	{
		printf("Memory limit reached. (~1GB)\n");
		return (0);
	}
	return (1);
}

int	validate(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments!\n");
		printf("\t<number_of_philosophers> [1 - ~8000000]\n");
		printf("\t<time_to_die>\n");
		printf("\t<time_to_eat>\n\t<time_to_sleep>\n");
		printf("\t[number_of_times_each_philosopher_must_eat] <- optional\n");
		return (0);
	}
	if (check_memory(ft_atoi(argv[1])) == 0)
		return (0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == 0)
		{
			printf(": index %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
