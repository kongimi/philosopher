/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:42:37 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/17 14:14:15 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

t_philo	**init_philo(char **argv, int argc)
{
	t_philo			**philo;
	int				num;
	int				i;

	num = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * num);
	i = 0;
	while (i < num)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->philo_num = num;
		philo[i]->name = i + 1;
		philo[i]->alive = 1;
		philo[i]->eat_num = 0;
		philo[i]->time_die = ft_atoi(argv[2]);
		philo[i]->time_eat = ft_atoi(argv[3]);
		philo[i]->time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i]->round_stop = ft_atoi(argv[5]);
		else
			philo[i]->round_stop = -1;
		i++;
	}
	return (philo);
}

pthread_mutex_t	**init_fork(int i)
{
	pthread_mutex_t	**forks;
	int				j;

	forks = malloc(sizeof(pthread_mutex_t) * i);
	j = 0;
	while (j < i)
	{
		forks[j] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[j], NULL);
		j++;
	}
	return (forks);
}

pthread_mutex_t	*init_mutex_prints(void)
{
	pthread_mutex_t	*mutex_prints;

	mutex_prints = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_prints, NULL);
	return (mutex_prints);
}

pthread_mutex_t	*init_exit(void)
{
	pthread_mutex_t	*all_exit;

	all_exit = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(all_exit, NULL);
	return (all_exit);
}
