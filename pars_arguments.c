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
	int	debug;

	i = 0;
	ft_atoi(argument, &debug);
	if (debug == FAILED)
	{
		printf("Error: Argument is not a valid number: %s\n", argument);
		return (FAILED);
	}
	if (argument[i] == '+' || argument[i] == '-')
		i++;
	while (argument[i])
	{
		if (argument[i] < '0' || argument[i] > '9')
		{
			printf("Error: Argument is not a valid number: %s\n", argument);
			return (FAILED);
		}
		i++;
	}
	return (SUCCESS);
}

int	pars_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid arguments\n");
		return (FAILED);
	}
	while (av[i])
	{
		if (all_is_numbers(av[i]) == FAILED)
			return (FAILED);
		i++;
	}
	return (SUCCESS);
}
