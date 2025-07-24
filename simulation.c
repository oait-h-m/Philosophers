/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 07:16:25 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/23 22:41:18 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_program	*info;

	info = (t_program *)data;
	printf("0 1 has taken a fork\n");
	ft_usleep(info->time_to_die);
	printf("%ld 1 died\n", info->time_to_die);
	return (NULL);
}

void	print_action(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->program->write_mutex);
	if (!philo->program->is_dead)
	{
		time = get_current_time() - philo->program->start_time;
		printf("%ld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->program->write_mutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->program->death_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->death_mutex);
	ft_usleep(philo->program->time_to_eat);
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo->program->is_dead)
	{
		ft_eat(philo);
		if (philo->program->is_dead)
			break ;
		pthread_mutex_lock(&philo->program->death_mutex);
		if (philo->program->number_of_meals != -1 
			&& philo->meals_eaten >= philo->program->number_of_meals)
		{
			pthread_mutex_unlock(&philo->program->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->program->death_mutex);
		print_action(philo, "is sleeping");
		ft_usleep(philo->program->time_to_sleep);
		if (philo->program->is_dead)
			break ;
		print_action(philo, "is thinking");
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
