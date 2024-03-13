/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:44 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/13 15:56:51 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// int	check_alive(t_philo *philo)
// {
// 	int	alive_time;

// 	alive_time = get_alive_time(philo->last_meal);
// 	if (alive_time > philo->time_die)
// 		return (0);
// 	return (1);
// }

int	prnt_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_print);
	printf("%d %s\n", philo->name, msg);
	pthread_mutex_unlock(philo->mutex_print);
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	prnt_msg("has taken forks.", philo);
	return (1);
}
