/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/07 16:43:33 by npiyapan         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc != 5 && argc != 6)
		handle_errors("Usage : amount_of_philo die eat sleep time_to_stop\n");
	if (check_argv(argv))
		handle_errors("Usage : input must be number or greather than 0.\n");
	if (argc == 6)
		data.stop = ft_atoi(argv[5]);
	else
		data.stop = -1;
	init_philo(&data, argv);
	return (0);
}
