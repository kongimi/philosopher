/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:20:13 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/09 11:18:09 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int		amount;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		stop;
}	t_philo;

typedef struct s_time
{
	time_t			t_sec;
}	t_time;

int		ft_atoi(const char *str);

void	handle_errors(char *error_msg);
void	init_philo(t_philo *data, char **argv);

__uint64_t	get_time(void);
