/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:46:09 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/03 11:24:36 by npiyapan         ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	prnt_msg(t_philo *philo, char *s)
{
	__uint64_t	now;

	if (pthread_mutex_lock(&philo->rule->mu_can_print) < 0)
		return ;
	if (philo->rule->can_print)
	{
		now = get_time();
		printf("%lu %d %s\n", now - philo->rule->start_time, philo->name, s);
	}
	pthread_mutex_unlock(&philo->rule->mu_can_print);
}

int	join_threads(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].thds, NULL);
		i++;
	}
	pthread_join(philo[0].monitor_thds, NULL);
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}
