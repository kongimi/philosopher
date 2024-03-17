/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:46:09 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/17 11:58:15 by npiyapan         ###   ########.fr       */
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

void	check_exit(t_philo *philo)
{
	pthread_mutex_lock(philo->all_exit);
	pthread_mutex_unlock(philo->all_exit);
}

int	check_alive(t_philo *philo)
{
	__uint64_t		now;

	now = get_time();
	philo->time_now = (int)(now - philo->last_meal);
	if (philo->time_now > philo->time_die)
	{
		pthread_mutex_lock(philo->all_exit);
		if (philo->alive)
			prnt_msg("died.", philo);
		pthread_mutex_unlock(philo->all_exit);
		philo->alive = 0;
		return (0);
	}
	return (1);
}
