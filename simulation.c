/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:00:00 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/12 00:00:00 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals_complete(t_program *data)
{
	int	i;
	int	all_ate_enough;

	if (data->number_of_meals == -1)
		return (0);
	all_ate_enough = 1;
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philo[i].meals_eaten < data->number_of_meals)
			all_ate_enough = 0;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (all_ate_enough);
}

static int	check_philosopher_death(t_program *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->death_mutex);
	time_since_last_meal = get_time() - data->philo[i].last_meal_time;
	if (time_since_last_meal >= data->time_to_die)
	{
		data->is_dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->write_mutex);
		printf("%ld %d died\n", get_time() - data->start_time, data->philo[i].id);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	check_death(t_program *data)
{
	int	i;

	while (!data->is_dead)
	{
		i = 0;
		while (i < data->n_of_philo && !data->is_dead)
		{
			if (check_philosopher_death(data, i))
				return (1);
			i++;
		}
		if (check_meals_complete(data))
		{
			data->is_dead = 1;
			return (0);
		}
		usleep(100);
	}
	return (1);
}

int	start_simulation(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, 
			philosopher_routine, &data->philo[i]))
			return (1);
		i++;
	}
	check_death(data);
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (0);
}

void	cleanup(t_program *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philo);
	free(data);
}
