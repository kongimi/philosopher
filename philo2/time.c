/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <niran.analas@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:14:58 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/28 22:41:12 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

uint64_t	get_time(void)
{
	struct timeval	my_time;

	if (gettimeofday(&my_time, NULL))
		return (0);
	return ((my_time.tv_sec * (uint64_t)1000) + (my_time.tv_usec / 1000));
}

int	get_alive_time(uint64_t start_time)
{
	uint64_t		my_time;

	my_time = get_time();
	return (my_time - start_time);
}

void	ft_usleep(uint64_t ms)
{
	uint64_t	start;
	uint64_t	now;

	start = get_time();
	now = start;
	while ((now - start) < ms)
	{
		usleep (300);
		now = get_time();
	}
}
