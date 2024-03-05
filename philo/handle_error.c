/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:17:59 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/05 14:02:55 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	handle_errors(char *error_msg)
{
	write(STDERR_FILENO, "Error: ", 7);
	int i;

	i = 0;
	while (error_msg[i])
		i++;
	write(STDERR_FILENO, error_msg, i);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
