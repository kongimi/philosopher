/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 16:15:59 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check_input(int argc, char **argv)
{
	int	n;
	int	sleep;
	int	eat;
	int	die;

	if (argc != 5 && argc != 6)
		handle_errors("Usage : amount_of_philo die eat sleep time_to_stop\n");
	if (check_argv(argv))
		handle_errors("Usage : input must be only number.\n");
	n = ft_atoi(argv[1]);
	if (n > 200 || n < 1)
		handle_errors("number of Philosopher must be 1 - 200");
	die = ft_atoi(argv[2]);
	eat = ft_atoi(argv[3]);
	sleep = ft_atoi(argv[4]);
	if (sleep < 60 || eat < 60 || die < 60)
		handle_errors("Time must greater than 59");
}

void	*philo_act(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Hello this is %d\n", philo->name);
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
	fork = init_fork(ft_atoi(argv[1]));
	threads = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	create_threads(ft_atoi(argv[1]), threads, philo);
	join_thread(threads, ft_atoi(argv[1]));
	free (threads);
	free_philo (philo);
	free_fork(ft_atoi(argv[1]), fork);
	return (0);
}
