/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/12 16:58:45 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*philo_act(void *data)
{
	t_philo			*philo;
	__uint64_t		now;
	int				diff;

	philo = (t_philo *)data;
	while (philo->alive)
	{
		// if (!take_forks(philo))
		// 	break ;
		// pthread_mutex_lock(philo->round_exit);
		// philo->round_eat++;
		// pthread_mutex_unlock(philo->round_exit);
		now = get_time();
		diff = (int)(now - philo->last_meal);
		// if (!check_alive(philo))
		// 	philo->alive = 0;
		if (diff >= philo->time_die)
			philo->alive = 0;
	}
	// prnt_msg("I'm die.", philo);
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

void	assign_fork(t_philo **philo, pthread_mutex_t **forks)
{
	int	n;
	int	i;

	n = philo[0]->philo_num;
	philo[0]->left_fork = forks[0];
	philo[0]->right_fork = forks[n - 1];
	i = 1;
	while (i < n)
	{
		philo[i]->left_fork = forks[i];
		philo[i]->right_fork = forks[i - 1];
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			**philo;
	pthread_mutex_t	**forks;
	pthread_t		*threads;

	check_input(argc, argv);
	philo = init_philo(argv, argc);
	set_time(philo, ft_atoi(argv[1]));
	forks = init_fork(ft_atoi(argv[1]));
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	create_threads(ft_atoi(argv[1]), threads, philo);
	join_thread(threads, ft_atoi(argv[1]));
	assign_fork(philo, forks);
	free (threads);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), forks);
	return (0);
}
