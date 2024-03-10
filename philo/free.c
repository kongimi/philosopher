/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:56:58 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 16:10:32 by npiyapan         ###   ########.fr       */
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
		free(data[i]);
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
