/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:43:35 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/14 15:45:30 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

#define  FAILED -1
#define  SUCCESS 1


typedef	struct s_program t_program;
typedef struct	s_philo t_philo;

int		pars_arguments(int ac, char **av);
long		ft_atoi(char *str, int *debug);
int		init_philo(t_program **data);
int		init_arguments(t_program **data, char **av);
long		get_current_time(void);
void		ft_usleep(long time);
void		*one_philo(void *data);


struct s_program
{
	long			n_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_meals;
	bool			is_dead;
	long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		death_mutex;
	t_philo			*philo;
};

struct	s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	t_program			*program;
};

#endif
