/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:00:00 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/07/12 00:00:00 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->program->forks[philo->l_fork]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->program->forks[philo->r_fork]);
		print_message(philo, "has taken a fork");
	}
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->program->forks[philo->r_fork]);
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->program->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->death_mutex);
	ft_usleep(philo->program->time_to_eat);
	drop_forks(philo);
}

static void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->program->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!philo->program->is_dead)
	{
		eat(philo);
		if (philo->program->number_of_meals != -1 
			&& philo->meals_eaten >= philo->program->number_of_meals)
			break;
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
