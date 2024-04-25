/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:28:33 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/14 12:37:49 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_eat_num(u_int64_t i, t_philo *philo)
{
	if ((i + 1) >= philo->rule->eat_num)
	{
		pthread_mutex_lock(&philo->rule->mu_meals);
		philo->rule->meals += 1;
		if (philo->rule->meals >= philo->rule->philo_num)
		{
			pthread_mutex_unlock(&philo->rule->mu_meals);
			unlock_forks(philo);
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
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_lock(&philo->rule->mu_meals);
	if (philo->rule->meals >= philo->rule->philo_num)
	{
		pthread_mutex_unlock(&philo->rule->mu_meals);
		return (0);
	}
	pthread_mutex_unlock(&philo->rule->mu_meals);
	ft_usleep(10);
	return (1);
}

void	destroy_mutex(t_philo *philo, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
	}
	pthread_mutex_destroy(&philo->rule->mu_can_print);
	pthread_mutex_destroy(&philo->rule->mu_meals);
}
