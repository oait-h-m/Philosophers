/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:30:36 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/26 16:00:19 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_program **data)
{
	int	i;

	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_of_philo);
	if (!(*data)->forks)
		return (FAILED);
	i = 0;
	while (i < (*data)->n_of_philo)
	{
		pthread_mutex_init(&(*data)->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&(*data)->write_mutex, NULL);
	pthread_mutex_init(&(*data)->death_mutex, NULL);
	return (SUCCESS);
}

int	init_philo(t_program **data)
{
	int	i;

	(*data)->st_philo = malloc(sizeof(t_philo) * (*data)->n_of_philo);
	if (!(*data)->st_philo)
		return (FAILED);
	i = 0;
	while (i < (*data)->n_of_philo)
	{
		(*data)->st_philo[i].id = i + 1;
		(*data)->st_philo[i].l_fork = i;
		(*data)->st_philo[i].r_fork = (i + 1) % (*data)->n_of_philo;
		(*data)->st_philo[i].meals_eaten = 0;
		(*data)->st_philo[i].last_meal_time = (*data)->start_time;
		(*data)->st_philo[i].program = *data;
		i++;
	}
	return (SUCCESS);
}

int	init_arguments(t_program **data, char **av)
{
	int	debug;

	*data = malloc(sizeof(t_program));
	if (!*data)
		return (FAILED);
	(*data)->n_of_philo = ft_atoi(av[1], &debug);
	(*data)->time_to_die = ft_atoi(av[2], &debug);
	(*data)->time_to_eat = ft_atoi(av[3], &debug);
	(*data)->time_to_sleep = ft_atoi(av[4], &debug);
	(*data)->is_dead = 0;
	(*data)->start_time = get_current_time();
	if (av[5])
		(*data)->number_of_meals = ft_atoi(av[5], &debug);
	else
		(*data)->number_of_meals = FAILED;
	if (init_forks(data) == FAILED || init_philo(data) == FAILED)
		return (FAILED);
	return (SUCCESS);
}
