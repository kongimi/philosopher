/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:10 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/30 17:11:40 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include <stdio.h>

static int	get_forks(t_philo *philo)
{
	if (philo->rule->philo_num == 1)
	{
		ft_usleep(philo->rule->time_die + 10);
		return (1);
	}
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->rule->mu_can_print);
	if (!philo->rule->can_print)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->rule->mu_can_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->rule->mu_can_print);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->rule->mu_can_print);
	if (!philo->rule->can_print)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->rule->mu_can_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->rule->mu_can_print);
	prnt_msg(philo, "has taken a fork.");
	return (0);
}

static int	eating(t_philo *philo)
{
	prnt_msg(philo, "is eating.");
	ft_usleep(philo->rule->time_eat);

	pthread_mutex_lock(&philo->rule->mu_can_print);
	if (!philo->rule->can_print)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->rule->mu_can_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->rule->mu_can_print);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	prnt_msg(philo, "is sleeping.");
	ft_usleep(philo->rule->time_sleep);
	return (0);
}

void	*ft_action(void *p)
{
	t_philo		*philo;
	__uint64_t	i;
	__uint64_t	j;

	i = 0;
	philo = (t_philo *) p;
	pthread_mutex_lock (&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if ((philo->name % 2) == 1)
		ft_usleep(10 + philo->name);
	while (i < philo->rule->eat_num)
	{
		if (get_forks(philo))
			break ;
		if (eating(philo))
			break ;
		j = i++;
		if (j < philo->rule->eat_num)
			break ;
		sleeping(philo);
		prnt_msg(philo, "is thinking.");
		i++;
	}
	prnt_msg(philo, "have eaten all of it.");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rule		rule;
	t_philo		*philo;

	check_input(argc, argv);
	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philo(&philo, &rule))
		return (1);
	if (init_threads(philo))
		return (1);
	join_threads(philo, rule.philo_num);
	free (philo);
	return (0);
}
