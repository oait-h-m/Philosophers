/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 07:16:25 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/16 07:18:20 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*one_philo(void *data)
{
	t_program	*info;

	info = (t_program *) data;
	printf("0 1 has taken a fork\n");
	ft_usleep(info->time_to_die);
	printf("%ld 1 died\n", info->time_to_die);
	return NULL;
}

void	*simulation(void *arg)
{
	return NULL;
}

void	*routine(t_program *philo)
{
	pthread_t	thread;
	int		i;

	i= 0;
	if (philo->number_of_meals == 0)
		return NULL;
	if (philo->philo->id % 2 == 0)
		usleep(1000);
	while (i < philo->n_of_philo)
	{
		pthread_create(&thread, NULL, simulation, arg);
		i++;
	}
	return NULL;
}
