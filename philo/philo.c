/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 17:10:45 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*philo_act(void *data)
{
	t_philo			*philo;
	__uint64_t		now;
	int				diff;

	philo = (t_philo *)data;
	printf("Hello this is %d\n", philo->name);
	while (philo->alive)
	{
		now = get_time();
		diff = (int)(now - philo->last_meal);
		if (diff >= philo->time_die)
			philo->alive = 0;
	}
	printf ("%d I'm %d die\n", diff, philo->name);
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
	pthread_mutex_t	**fork;
	pthread_t		*threads;

	check_input(argc, argv);
	philo = init_philo(argv, argc);
	set_time(philo, ft_atoi(argv[1]));
	fork = init_fork(ft_atoi(argv[1]));
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	create_threads(ft_atoi(argv[1]), threads, philo);
	join_thread(threads, ft_atoi(argv[1]));
	free (threads);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), fork);
	return (0);
}
