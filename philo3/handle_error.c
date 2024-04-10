/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:17:59 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/10 17:10:37 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	handle_errors(char *error_msg)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "Error: ", 7);
	while (error_msg[i])
		i++;
	write(STDERR_FILENO, error_msg, i);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
