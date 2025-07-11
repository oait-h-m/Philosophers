/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:30:36 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/09 18:01:04 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_arguments(t_program **data, char **av)
{
	*data = malloc(sizeof(t_program));
	if (!*data)
		return ;
	(*data)->n_of_philo = ft_atoi(av[1], 0);
	(*data)->time_to_die = ft_atoi(av[2], 0);
	(*data)->time_to_eat = ft_atoi(av[3], 0);
	(*data)->time_to_sleep = ft_atoi(av[4], 0);
	if (av[5])
		(*data)->number_of_meals = ft_atoi(av[5], 0);
}

void	init_philo(t_program *data)
{
	t_philo	philo;

	data->philo = malloc(sizeof(t_philo) * data->n_of_philo);
}
