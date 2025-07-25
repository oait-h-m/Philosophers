/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:37:58 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/23 22:50:03 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program	*data;
	pthread_t	t1;

	if (pars_arguments(ac, av) == FAILED)
		return (FAILED);
	if (init_arguments(&data, av) == FAILED || data->n_of_philo == 0 || data->number_of_meals == 0)
		return (FAILED);
	if (data->n_of_philo == 1)
	{
		pthread_create(&t1, NULL, one_philo, data);
		pthread_join(t1, NULL);
	}
	else
	{
		simulation(data);
	}
	ft_free(data);
}
