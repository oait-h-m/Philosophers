/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:43:00 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/09 18:02:59 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program	*info;

	if (pars_arguments(ac, &av[1]) == 0)
		return (-1);
	init_program_info(&info, av);
	if (!info)
		return (-1);
	if (info->n_of_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(info->time_to_die);
		printf("%ld 1 died\n", info->time_to_die);
		cleanup(info);
		return (0);
	}
	start_simulation(info);
	cleanup(info);
	return (0);
}
