/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:26:12 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/14 12:43:49 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include <stdio.h>

void	set_can_print(t_philo *p)
{
	pthread_mutex_lock(&p[0].rule->mu_can_print);
	p[0].rule->can_print = 0;
	pthread_mutex_unlock(&p[0].rule->mu_can_print);
}

void	monitor_loop(t_philo *p, t_rule *p_rule)
{
	int			i;

	i = -1;
	while (++i < p_rule->philo_num)
	{
		pthread_mutex_lock(&p[i].mutex_last_meal);
		if (get_alive_time(p[i].last_meal) > p_rule->time_die)
		{
			prnt_msg(&p[i], "died");
			pthread_mutex_lock(&p[i].rule->mu_can_print);
			p[i].rule->can_print = 0;
			pthread_mutex_unlock(&p[i].rule->mu_can_print);
		}
		pthread_mutex_unlock(&p[i].mutex_last_meal);
		pthread_mutex_lock(&p[0].rule->mu_meals);
		if (p[0].rule->meals >= (p[0].rule->philo_num))
			set_can_print(&p[0]);
		pthread_mutex_unlock(&p[0].rule->mu_meals);
		ft_usleep(1);
	}
}

void	*ft_monitor(void *p)
{
	t_philo	*philo;
	t_rule	*p_rule;

	philo = (t_philo *) p;
	p_rule = philo[0].rule;
	while (1)
	{
		monitor_loop(philo, p_rule);
		pthread_mutex_lock(&philo[0].rule->mu_can_print);
		if (philo[0].rule->can_print == 0)
		{
			pthread_mutex_unlock(&philo[0].rule->mu_can_print);
			break ;
		}
		pthread_mutex_unlock(&philo[0].rule->mu_can_print);
	}
	return (NULL);
}
