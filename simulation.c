/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 07:16:25 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/26 15:57:40 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_program	*info;

	info = (t_program *)data;
	printf("0 1 has taken a fork\n");
	ft_usleep(info->time_to_die, info);
	printf("%ld 1 died\n", info->time_to_die);
	return (NULL);
}

void	print_action(t_philo *philo, char *str)
{
	long	time;
	int		should_print;

	pthread_mutex_lock(&philo->program->death_mutex);
	should_print = !philo->program->is_dead;
	pthread_mutex_unlock(&philo->program->death_mutex);
	if (should_print)
	{
		pthread_mutex_lock(&philo->program->write_mutex);
		pthread_mutex_lock(&philo->program->death_mutex);
		if (!philo->program->is_dead)
		{
			time = get_current_time() - philo->program->start_time;
			printf("%ld %d %s\n", time, philo->id, str);
		}
		pthread_mutex_unlock(&philo->program->death_mutex);
		pthread_mutex_unlock(&philo->program->write_mutex);
	}
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
		print_action(philo, "has taken a fork");
	}
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->program->death_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->death_mutex);
	ft_usleep(philo->program->time_to_eat, philo->program);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(philo->program))
	{
		ft_eat(philo);
		if (is_simulation_over(philo->program))
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(philo->program->time_to_sleep, philo->program);
		if (is_simulation_over(philo->program))
			break ;
		print_action(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}

int	simulation(t_program *data)
{
	pthread_t	thread;
	int			i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->n_of_philo)
	{
		data->st_philo[i].last_meal_time = data->start_time;
		pthread_create(&data->st_philo[i].thread, NULL, routine,
			&data->st_philo[i]);
		i++;
	}
	pthread_create(&thread, NULL, ft_monitor, data);
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_join(data->st_philo[i].thread, NULL);
		i++;
	}
	pthread_join(thread, NULL);
	return (SUCCESS);
}
