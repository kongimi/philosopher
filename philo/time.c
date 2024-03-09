/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:14:58 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/09 11:34:45 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

__uint64_t	get_time(void)
{
	struct timeval	my_time;

	if (gettimeofday(&my_time, NULL))
		return (0);
	return ((my_time.tv_sec * (__uint64_t)1000) + (my_time.tv_usec / 1000));
}
