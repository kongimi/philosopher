/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:10 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/24 18:07:22 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*routine(void *arg)
{

}

int main(int argc, char **argv)
{
	t_rule		rule;
	t_philo		*philo;
	pthread_t	*threads;

	check_input(argc, argv);
	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philo(&philo, &rule))
		return (1);
	if (init_threads(threads, philo))
		return (1);
	free (philo);
	return (0);
}