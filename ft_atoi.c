/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-h-m <oait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:21:06 by oait-h-m          #+#    #+#             */
/*   Updated: 2025/06/30 22:35:39 by oait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_sign(char *str, int *sign, int *i)
{
	if (str[*i] == '-')
		*sign = -1;
	(*i)++;
}

long	ft_atoi(char *str, int *debug)
{
	int			i;
	int			sign;
	long			result;

	result = 0;
	i = 0;
	sign = 1;
	*debug = 1;
	if (str[i] == '-' || str[i] == '+')
		is_sign(str, &sign, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (result > INT_MAX || result < INT_MIN)
			*debug = -1;
		i++;
	}
	return (result * sign);
}
