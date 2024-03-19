/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/19 15:37:09 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*philo_act(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	philo->last_meal = get_time();
	if (((philo->name + 1) % 2) == 0)
	{
		usleep(philo->time_sleep * (1000));
		prnt_msg("is thinking", philo);
	}
	while (philo->alive)
	{
		take_forks(philo);
		if (!check_alive(philo))
			break ;
		eating(philo);
		if (!check_alive(philo))
			break ;
		sleeping(philo);
		if (!check_alive(philo))
			break ;
		prnt_msg("is thinking", philo);
		if (!check_alive(philo))
			break ;
		usleep(10);
	}
	return (NULL);
}

void	create_threads(int num, pthread_t *thread, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_create(&thread[i], NULL, &philo_act, philo[i]);
		i++;
	}
}

void	join_thread(pthread_t *thread, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

void	*monitor_all(void *data)
{
	t_philo	**philo;
	int		i;
	int		num;

	i = 0;
	philo = (t_philo **) data;
	num = philo[i]->philo_num;
	while (1)
	{
		if (!philo[i]->alive)
		{
			i = 0;
			while (i < num)
			{
				philo[i]->alive = 0;
				i++;
			}
			break ;
		}
		i++;
		if (i >= num)
			i = 0;
		usleep(10);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*mutex_prints;

	check_input(argc, argv);
	philo = init_philo(argv, argc);
	set_time(philo, ft_atoi(argv[1]));
	forks = init_fork(ft_atoi(argv[1]));
	mutex_prints = init_mutex_prints();
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	assign_fork(philo, forks);
	assign_mutex_print(philo, mutex_prints);
	create_threads(ft_atoi(argv[1]), threads, philo);
	pthread_create(&monitor, NULL, &monitor_all, philo);
	join_thread(threads, ft_atoi(argv[1]));
	pthread_join(monitor, NULL);
	free (threads);
	free_prints(mutex_prints);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), forks);
	return (0);
}
