/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:35:08 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/24 18:03:56 by npiyapan         ###   ########.fr       */
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
	rule->eat_num = -1;
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

void init_r_fork(t_philo *p)
{
	int i;
	int num;

	i = 0;
	num = p[0].rule->philo_num;
	while (i < num)
	{
		p[i].r_fork = &p[(i + 1) % num].l_fork;
		i++;
	}
}

int	init_philo(t_philo **philo, t_rule *rule)
{
	t_philo *p;
	t_tmp	tmp;

	p = malloc (sizeof(t_philo) * rule->philo_num);
	if (!p)
	{
		pthread_mutex_destroy(&rule->mu_can_print);
		write (2, "malloc error init_philo\n", 24);
		return (1);
	}
	memset(p, 0, sizeof(t_philo) * rule->philo_num);
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
	init_r_fork(p);
	*philo = p;
	return (0);
}

int	init_threads(pthread_t *threads, t_philo *philo)
{
	int i;
	int num;

	i = 0;
	num = philo[i].rule->philo_num;
	while (i < num)
	{
		pthread_create(&threads[i], NULL, &routine, &philo[i]);
		i++;
	}
	return (0);
}