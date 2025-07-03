/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:31:24 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/03 22:31:36 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	all_is_numbers(char *argument)
{
	int	i;

	i = 0;
	if (argument[i] == '-' || argument[i] == '+')
		i++;
	while (argument[i])
	{
		if (argument[i] < '0' || argument[i] > '9')
		{
			printf("Error: Argument %d is not a valid number: %s\n", i, argument);
			return 0;
		}
		i++;
	}
	return 1;
}

int	pars_arguments(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");

		return 0;
	}
	while (av[i])
	{
		if (!all_is_numbers(av[i]))
			return 0;
		i++;
	}
	return 1;
}
