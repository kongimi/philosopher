/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:26:12 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/30 17:06:38 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	monitor_loop(t_philo *p, t_rule *p_rule)
{
	int			i;
	int			last_meal;

	i = 0;
	while (i < p_rule->philo_num)
	{
		pthread_mutex_lock(&p[i].mutex_last_meal);
		last_meal = get_alive_time(p[i].last_meal);
		pthread_mutex_unlock(&p[i].mutex_last_meal);
		if ( last_meal > p_rule->time_die)
		{
			prnt_msg(p, "DIE");
			pthread_mutex_lock(&p[i].rule->mu_can_print);
			p[i].rule->can_print = 0;
			pthread_mutex_unlock(&p[i].rule->mu_can_print);
		}
		usleep(10);
		i++;
	}
}

void	*ft_monitor(void *p)
{
	t_philo	*philo;
	t_rule	*p_rule;
	int		i;

	philo = (t_philo *) p;
	p_rule = philo[0].rule;
	while (philo[0].rule->can_print)
		monitor_loop(philo, p_rule);
	i = 0;
	ft_usleep(1000);
	while (i < philo->rule->philo_num)
	{
		pthread_mutex_destroy(&philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
		i++;
	}
	pthread_mutex_destroy(&p_rule->mu_can_print);
	return (NULL);
}
