/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:46:09 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 17:04:55 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	mul;

	i = 0;
	res = 0;
	mul = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		mul = -1;
	if ((mul == -1) || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * mul);
}

void	set_time(t_philo **philo, int n)
{
	__uint64_t	my_time;
	int			i;

	my_time = get_time();
	i = 0;
	while (i < n)
	{
		philo[i]->last_meal = my_time;
		i++;
	}
}
