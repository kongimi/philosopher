/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:42:21 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/19 10:10:30 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*check_die(void *philo_input)
{
	t_philo	**philos;
	int		i;
	int		num;

	i = 0;
	philos = (t_philo **) philo_input;
	num = philos[i]->philo_num;
	while (1)
	{
		if (!(philos[i]->alive))
			break ;
		i++;
		if (i >= num)
			i = 0;
	}
	return (NULL);
}
