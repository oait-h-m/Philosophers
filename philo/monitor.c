/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:42:45 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/26 17:32:22 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_die(t_program **data, int i)
{
	(*data)->is_dead = 1;
	pthread_mutex_unlock(&(*data)->death_mutex);
	pthread_mutex_lock(&(*data)->write_mutex);
	printf("%ld %d died\n", get_current_time() - (*data)->start_time,
		(*data)->st_philo[i].id);
	pthread_mutex_unlock(&(*data)->write_mutex);
}

int	check_philosopher_death(t_program *data, int i)
{
	long	time_since_meal;

	pthread_mutex_lock(&data->death_mutex);
	time_since_meal = get_current_time() - data->st_philo[i].last_meal_time;
	if (time_since_meal > data->time_to_die)
	{
		philo_is_die(&data, i);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	check_meals_finished(t_program *data, int i)
{
	int	finished;

	pthread_mutex_lock(&data->death_mutex);
	if (data->number_of_meals != -1
		&& data->st_philo[i].meals_eaten >= data->number_of_meals)
		finished = 1;
	else
		finished = 0;
	pthread_mutex_unlock(&data->death_mutex);
	return (finished);
}

int	is_simulation_over(t_program *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	*ft_monitor(void *arg)
{
	t_program	*data;
	int			finish;

	data = (t_program *)arg;
	while (!is_simulation_over(data))
	{
		finish = check_all_philosophers(data);
		if (finish == FAILED)
			return (NULL);
		if (data->number_of_meals != -1 && finish == data->n_of_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
