/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:42:37 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/09 17:11:15 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*print_hello(void *args)
{
	t_philo		*philo;
	__uint64_t	my_time;

	philo = (t_philo *)args;
	printf("amount in thread = %d\n", philo->amount);
	while (philo->alive)
	{
		my_time = get_time();
		if (my_time)
			printf("time = %ld\n", my_time);
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
	data->amount = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->alive = 1;
}
