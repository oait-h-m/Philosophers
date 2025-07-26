/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:43:35 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/26 17:34:19 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FAILED -1
# define SUCCESS 1

typedef struct s_program	t_program;
typedef struct s_philo		t_philo;

int							pars_arguments(int ac, char **av);
long						ft_atoi(char *str, int *debug);
int							init_philo(t_program **data);
int							init_arguments(t_program **data, char **av);
long						get_current_time(void);
void						ft_usleep(long time, t_program *data);
void						*one_philo(void *data);
void						ft_eat(t_philo *philo);
int							simulation(t_program *data);
int							is_simulation_over(t_program *data);
void						philo_is_die(t_program **data, int i);
int							is_simulation_over(t_program *data);
int							check_meals_finished(t_program *data, int i);
int							check_all_philosophers(t_program *data);
int							check_philosopher_death(t_program *data, int i);
void						*ft_monitor(void *arg);
void						ft_free(t_program *data);

struct						s_program
{
	long					n_of_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					number_of_meals;
	int						is_dead;
	long					start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			death_mutex;
	t_philo					*st_philo;
};

struct						s_philo
{
	int						id;
	int						l_fork;
	int						r_fork;
	int						meals_eaten;
	long					last_meal_time;
	pthread_t				thread;
	t_program				*program;
};

#endif
