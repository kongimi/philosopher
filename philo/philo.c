/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:11:51 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/03 16:43:35 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	check_argv(char **argv)
{
	int	i;
	// int	j;

	i = 1;
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 6)
		handle_errors("Usage : num_philo die eat sleep eat2\n");
	if (check_argv(argv))
		handle_errors("input must be number.\n");
	return (0);
}
