/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:31 by amaula            #+#    #+#             */
/*   Updated: 2024/10/18 13:33:38 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Parses string into int while checking for errors
 * Return value must be >= 0
 * 0 indicates an error:
 * 	- Overflow error: when more than INT_MAX
 * 	- Value error: when 0 or non-numeric chars are encountered */
unsigned int	parse_string(char *string)
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
	if (*string || ret == 0)
	{
		printf("Value error");
		return (0);
	}
	return ((int)ret);
}

/* Checks if users input is valid */
int	validate(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong amount of arguments!\n");
		return (0);
	}
	if (parse_string(argv[1]) > 1000)
	{
		printf("Too many philosophers.\n");
		return (0);
	}
	while (i < argc)
	{
		if (parse_string(argv[i]) == 0)
		{
			printf(": index %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
