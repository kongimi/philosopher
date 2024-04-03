/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:28:33 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/03 15:55:08 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_eat_num(u_int64_t i, t_philo *philo)
{
	if ((i + 1) >= philo->rule->eat_num)
	{
		printf("test\n");
		pthread_mutex_lock(&philo->rule->mu_meals);
		philo->rule->meals += 1;
		if (philo->rule->meals >= philo->rule->philo_num)
		{
			pthread_mutex_unlock(&philo->rule->mu_meals);
			unlock_forks(philo);
			printf("test2\n");
			return (1);
		}
		pthread_mutex_unlock(&philo->rule->mu_meals);
	}
	return (0);
}

void	inc_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->rule->mu_meals);
	philo->rule->meals += 1;
	pthread_mutex_unlock(&philo->rule->mu_meals);
}

int	wait_meals(t_philo *philo)
{
	ft_usleep(10);
	pthread_mutex_lock(&philo->rule->mu_meals);
	if (philo->rule->meals >= philo->rule->philo_num)
	{
		pthread_mutex_unlock(&philo->rule->mu_meals);
		return (0);
	}
	pthread_mutex_unlock(&philo->rule->mu_meals);
	return (1);
}
