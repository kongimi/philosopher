/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:44 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/19 14:40:05 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	get_time_now(t_philo *philo)
{
	philo->time_now = get_time() - philo->last_meal;
}

int	prnt_msg(char *msg, t_philo *philo)
{
	if (philo->alive)
	{
		get_time_now(philo);
		pthread_mutex_lock(philo->mutex_print);
		if (philo->alive)
			printf("%lu %d %d %s\n", get_time(), philo->time_now, philo->name, msg);
		pthread_mutex_unlock(philo->mutex_print);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!check_alive(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo->philo_num > 1)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!check_alive(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
	}
	else
	{
		usleep((philo->time_die * 1001));
		get_time_now(philo);
		check_alive(philo);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	prnt_msg("is eating", philo);
	// usleep(philo->time_eat * 1000);
	usleep(philo->time_eat * (1000 + philo->name) );
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!check_alive(philo))
		return (0);
	philo->last_meal = get_time();
	if (philo->round_stop != -1)
	{
		philo->eat_num++;
		if (philo->eat_num >= philo->round_stop)
		{
			prnt_msg("is eat enough.", philo);
			philo->alive = 0;
		}
	}
	return (1);
}

int	sleeping(t_philo *philo)
{
	prnt_msg("is sleeping", philo);
	// usleep(philo->time_sleep * 1000);
	usleep(philo->time_sleep * (1000 + philo->name) );
	check_alive(philo);
	return (0);
}
