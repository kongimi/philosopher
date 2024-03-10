/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:20:13 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/10 17:04:13 by npiyapan         ###   ########.fr       */
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
	int				philo_num;
	int				name;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				round_stop;
	int				alive;
	__uint64_t		last_meal;
}	t_philo;

int				ft_atoi(const char *str);
int				check_argv(char **argv);

void			handle_errors(char *error_msg);
void			free_philo(t_philo **data);
void			free_fork(int i, pthread_mutex_t **fork);
void			set_time(t_philo **philo, int n);
void			check_input(int argc, char **argv);

t_philo			**init_philo(char **argv, int argc);

pthread_mutex_t	**init_fork(int i);

__uint64_t		get_time(void);
