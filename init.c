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

void	init_program_info(t_program **data, char **av)
{
	int	debug;
	int	i;

	*data = malloc(sizeof(t_program));
	if (!*data)
		return ;
	(*data)->n_of_philo = ft_atoi(av[1], &debug);
	(*data)->time_to_die = ft_atoi(av[2], &debug);
	(*data)->time_to_eat = ft_atoi(av[3], &debug);
	(*data)->time_to_sleep = ft_atoi(av[4], &debug);
	(*data)->is_dead = 0;
	(*data)->start_time = get_time();
	if (av[5])
		(*data)->number_of_meals = ft_atoi(av[5], &debug);
	else
		(*data)->number_of_meals = -1;
	
	// Initialize mutexes
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_of_philo);
	if (!(*data)->forks)
		return ;
	i = 0;
	while (i < (*data)->n_of_philo)
	{
		pthread_mutex_init(&(*data)->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&(*data)->write_mutex, NULL);
	pthread_mutex_init(&(*data)->death_mutex, NULL);
	
	init_philo(*data);
}

void	init_philo(t_program *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->n_of_philo);
	if (!data->philo)
		return ;
	i = 0;
	while (i < data->n_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->n_of_philo;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = data->start_time;
		data->philo[i].program = data;
		i++;
	}
}
