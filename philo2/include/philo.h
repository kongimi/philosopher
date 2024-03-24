/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:46 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/24 18:05:51 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_tmp
{
	int	i;
	int	j;
	int	k;
}	t_tmp;


typedef struct s_rule
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				alive;
	int				eat_num;
	pthread_mutex_t	mu_can_print;
	int				can_print;
}	t_rule;

typedef struct s_philo
{
	__uint64_t		last_meal;
	int				name;
	struct s_rule	*rule;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

void			check_input(int argc, char **argv);
void			handle_errors(char *error_msg);
void 			init_r_fork(t_philo *p);

int				ft_atoi(const char *str);
int				init_rule(t_rule *rule, int argc, char **argv);
int				init_philo(t_philo **philo, t_rule *rule);
int				init_threads(pthread_t *threads, t_philo *philo);
