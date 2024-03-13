/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/13 16:53:33 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	eating(t_philo *philo)
{
	prnt_msg("eating", philo);
	usleep(philo->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	prnt_msg("sleeping", philo);
	usleep(philo->time_sleep);
	return (0);
}

void	thinking(t_philo *philo)
{
	prnt_msg("thinking", philo);
}

void	*philo_act(void *data)
{
	t_philo			*philo;
	__uint64_t		now;
	int				diff;

	philo = (t_philo *)data;
	while (philo->alive)
	{
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		now = get_time();
		diff = (int)(now - philo->last_meal);
		if (diff >= philo->time_die)
			philo->alive = 0;
	}
	prnt_msg("I'm die.", philo);
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

	check_input(argc, argv);
	philo = init_philo(argv, argc);
	set_time(philo, ft_atoi(argv[1]));
	forks = init_fork(ft_atoi(argv[1]));
	mutex_prints = init_mutex_prints();
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	assign_fork(philo, forks);
	assign_mutex_print(philo, mutex_prints);
	create_threads(ft_atoi(argv[1]), threads, philo);
	join_thread(threads, ft_atoi(argv[1]));
	free (threads);
	free_prints(mutex_prints);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), forks);
	return (0);
}
