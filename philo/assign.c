/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:25:43 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/16 16:20:00 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	assign_fork(t_philo **philo, pthread_mutex_t **forks)
{
	int	n;
	int	i;

	n = philo[0]->philo_num;
	philo[0]->left_fork = forks[0];
	philo[0]->right_fork = forks[n - 1];
	i = 1;
	while (i < n)
	{
		philo[i]->left_fork = forks[i];
		philo[i]->right_fork = forks[i - 1];
		i++;
	}
}

void	assign_mutex_print(t_philo **philo, pthread_mutex_t *mutex_print)
{
	int	n;
	int	i;

	n = philo[0]->philo_num;
	i = 0;
	while (i < n)
	{
		philo[i]->mutex_print = mutex_print;
		i++;
	}
}

void	assign_mutex_exit(t_philo **philo, pthread_mutex_t *all_exit)
{
	int	n;
	int	i;

	n = philo[0]->philo_num;
	i = 0;
	while (i < n)
	{
		philo[i]->all_exit = all_exit;
		i++;
	}
}
