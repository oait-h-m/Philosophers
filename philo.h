/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:43:35 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/09 18:01:41 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef	struct s_program t_program;
typedef struct	s_philo t_philo;

int	pars_arguments(int ac, char **av);
long	ft_atoi(char *str, int *debug);
void	init_program_info(t_program **data, char **av);


typedef	struct s_program
{
	int	n_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	t_philo	*philo;

}		t_program;

typedef struct	s_philo
{
	int	id;
	int	l_fork;
	int	r_fork;

}		t_philo;

#endif
