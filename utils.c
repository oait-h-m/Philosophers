/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:21:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/23 22:49:20 by oait-h-m         ###   ########.fr       */
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

void	ft_usleep(long time)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(100);
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
