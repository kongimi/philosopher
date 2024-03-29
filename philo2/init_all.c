/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <niran.analas@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:35:08 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/29 23:23:08 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	init_rule(t_rule *rule, int argc, char **argv)
{
	rule->alive = 1;
	rule->philo_num = ft_atoi(argv[1]);
	rule->time_die = ft_atoi(argv[2]);
	rule->time_eat = ft_atoi(argv[3]);
	rule->time_sleep = ft_atoi(argv[4]);
	rule->eat_num = INT64_MAX;
	rule->can_print = 1;
	if (argc == 6)
		rule->eat_num = ft_atoi(argv[5]);
	if (pthread_mutex_init(&rule->mu_can_print, NULL))
	{
		write(2, "Fail init mutex", 15);
		return (1);
	}
	return (0);
}

void	init_r_fork(t_philo *p)
{
	int	i;
	int	num;

	i = 0;
	num = p[0].rule->philo_num;
	while (i < num)
	{
		p[i].r_fork = &p[(i + 1) % num].l_fork;
		i++;
	}
}

int	init_each(t_philo *p, t_rule *rule)
{
	t_tmp	tmp;

	tmp.i = 0;
	while (tmp.i < rule->philo_num)
	{
		p[tmp.i].name = tmp.i + 1;
		p[tmp.i].rule = rule;
		tmp.j = pthread_mutex_init(&p[tmp.i].l_fork, NULL);
		tmp.k = pthread_mutex_init(&p[tmp.i].mutex_last_meal, NULL);
		if (tmp.j || tmp.k)
		{
			while (--tmp.i >= 0)
			{
				pthread_mutex_destroy(&p[tmp.i].l_fork);
				pthread_mutex_destroy(&p[tmp.i].mutex_last_meal);
			}
			pthread_mutex_destroy(&rule->mu_can_print);
			free (p);
			return (1);
		}
		tmp.i++;
	}
	return (0);
}

int	init_philo(t_philo **philo, t_rule *rule)
{
	t_philo	*p;
	t_tmp	tmp;

	p = (t_philo *)malloc (sizeof(t_philo) * rule->philo_num);
	if (!p)
	{
		pthread_mutex_destroy(&rule->mu_can_print);
		write (2, "malloc error init_philo\n", 24);
		return (1);
	}
	memset(p, 0, sizeof(t_philo) * rule->philo_num);
	if (init_each(p, rule))
		return (1);
	init_r_fork(p);
	*philo = p;
	return (0);
}

int	init_threads(t_philo *philo)
{
	int	i;
	int	num;

	i = 0;
	num = philo[i].rule->philo_num;
	while (i < num)
	{
		if (pthread_create(&philo[i].thds, NULL, &ft_action, &philo[i]))
		{
			write(2, "Fail create thread\n", 19);
			exit (1);
		}
		i++;
	}
	if (pthread_create(&philo[0].monitor_thds, NULL, &ft_monitor, philo))
	{
		write(2, "Fail create monitor thread\n", 27);
		exit (1);
	}
	return (0);
}
