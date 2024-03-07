/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:42:37 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/07 17:05:27 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*print_hello(void *arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (i++ < 100)
	{
		printf("Hello ");
		usleep(1000000);
	}
	return (NULL);
}

void	*print_world(void *arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (i++ < 100)
	{
		printf("World\n");
		usleep(1000000);
	}
	return (NULL);
}

void	init_philo(t_philo *data, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	data->amount = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	printf("amount = %d\n", data->amount);
	printf("die = %d\n", data->time_die);
	printf("eat = %d\n", data->time_eat);
	printf("sleep = %d\n", data->time_sleep);
	printf("stop = %d\n", data->stop);
	if (data->amount <= 0 || data->amount > 200 ||\
		data->time_die <= 0 || data->time_eat <= 0 ||\
		data->time_sleep <= 0)
		handle_errors("Input must greater than 0.");
	if (pthread_create(&t1, NULL, print_hello, NULL))
		handle_errors("Thread T1 error");
	if (pthread_create(&t2, NULL, print_world, NULL))
		handle_errors("Thread T2 error");
	if (pthread_join(t1, NULL))
		handle_errors("join T1 error");
	if (pthread_join(t2, NULL))
		handle_errors("join T2 error");
}
