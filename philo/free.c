/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:56:58 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/16 14:55:42 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	free_philo(t_philo **data)
{
	int	i;
	int	j;

	i = 0;
	j = data[i]->philo_num;
	while (i < j)
	{
		free (data[i]);
		i++;
	}
	free (data);
}

void	free_fork(int i, pthread_mutex_t **fork)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(fork[j]);
		free (fork[j]);
		j++;
	}
	free (fork);
}

void	free_prints(pthread_mutex_t *mutex_print)
{
	pthread_mutex_destroy(mutex_print);
	free (mutex_print);
}

void	free_all_exit(pthread_mutex_t *all_exit)
{
	pthread_mutex_destroy(all_exit);
	free (all_exit);
}
