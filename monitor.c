/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:42:45 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/23 21:42:47 by oait-h-m         ###   ########.fr       */
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
	if (time_since_meal >= data->time_to_die)
	{
		philo_is_die(&data, i);
		return (1);
	}
	return (0);
}

int	check_meals_finished(t_program *data, int i)
{
	if (data->number_of_meals != -1
		&& data->st_philo[i].meals_eaten >= data->number_of_meals)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_program	*data;
	int			i;
	int			finish;

	data = (t_program *)arg;
	while (!data->is_dead)
	{
		i = 0;
		finish = 0;
		while (i < data->n_of_philo && !data->is_dead)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			finish += check_meals_finished(data, i);
			i++;
		}
		if (data->number_of_meals != -1 && finish == data->n_of_philo)
		{
			data->is_dead = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
