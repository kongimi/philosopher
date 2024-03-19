/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:20:13 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/19 10:13:04 by npiyapan         ###   ########.fr       */
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
	int				time_now;
	int				eat_num;
	__uint64_t		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex_print;
}	t_philo;

int				ft_atoi(const char *str);
int				check_argv(char **argv);
int				prnt_msg(char *msg, t_philo *philo);
int				take_forks(t_philo *philo);
int				check_alive(t_philo *philo);
int				get_alive_time(__uint64_t start_time);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);

void			handle_errors(char *error_msg);
void			free_philo(t_philo **data);
void			free_fork(int i, pthread_mutex_t **fork);
void			free_prints(pthread_mutex_t *mutex_print);
void			set_time(t_philo **philo, int n);
void			check_input(int argc, char **argv);
void			assign_fork(t_philo **philo, pthread_mutex_t **forks);
void			assign_mutex_print(t_philo **philo, pthread_mutex_t *mu_print);
void			*check_die(void *philo_input);

t_philo			**init_philo(char **argv, int argc);

pthread_mutex_t	**init_fork(int i);
pthread_mutex_t	*init_mutex_prints(void);
pthread_mutex_t	*init_exit(void);

__uint64_t		get_time(void);
