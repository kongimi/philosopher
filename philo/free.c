/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:56:58 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 15:06:34 by npiyapan         ###   ########.fr       */
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
