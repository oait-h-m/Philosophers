/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:37:13 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/26 17:37:17 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str, int *debug)
{
	int		i;
	long	result;

	result = 0;
	i = 0;
	*debug = SUCCESS;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*debug = FAILED;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (result > INT_MAX || result < INT_MIN)
			*debug = FAILED;
		i++;
	}
	return (result);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time, t_program *data)
{
	long	start;
	int		is_dead;

	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		pthread_mutex_lock(&data->death_mutex);
		is_dead = data->is_dead;
		pthread_mutex_unlock(&data->death_mutex);
		if (is_dead)
			return ;
		usleep(100);
	}
}

int	check_all_philosophers(t_program *data)
{
	int	i;
	int	finish;

	i = 0;
	finish = 0;
	while (i < data->n_of_philo && !is_simulation_over(data))
	{
		if (check_philosopher_death(data, i))
			return (FAILED);
		if (check_meals_finished(data, i))
			finish++;
		i++;
	}
	return (finish);
}

void	ft_free(t_program *data)
{
	int	i;

	if (data)
	{
		if (data->forks)
		{
			i = 0;
			while (i < data->n_of_philo)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		pthread_mutex_destroy(&data->write_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		if (data->st_philo)
			free(data->st_philo);
		free(data);
	}
}
