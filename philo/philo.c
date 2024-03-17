/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/17 14:58:28 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*philo_act(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	philo->last_meal = get_time();
	if ((philo->name % 2) == 0)
	{
		usleep(philo->time_sleep);
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

int	main(int argc, char **argv)
{
	t_philo			**philo;
	pthread_t		*threads;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*mutex_prints;
	pthread_mutex_t	*all_exit;
	// int				i;

	check_input(argc, argv);
	philo = init_philo(argv, argc);
	set_time(philo, ft_atoi(argv[1]));
	forks = init_fork(ft_atoi(argv[1]));
	mutex_prints = init_mutex_prints();
	all_exit = init_exit();
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	assign_fork(philo, forks);
	assign_mutex_print(philo, mutex_prints);
	assign_mutex_exit(philo, all_exit);
	create_threads(ft_atoi(argv[1]), threads, philo);
	join_thread(threads, ft_atoi(argv[1]));
	// i = 0;
	// while (1)
	// {
	// 	while (!philo[1]->alive)
	// 	{
	// 		i++;
	// 		if (i >= philo[i]->philo_num)
	// 			i = 0;
	// 		break;
	// 	}
	// }
	free (threads);
	free_prints(mutex_prints);
	free_all_exit(all_exit);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), forks);
	return (0);
}
