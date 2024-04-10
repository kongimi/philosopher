/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:46 by npiyapan          #+#    #+#             */
/*   Updated: 2024/04/10 17:11:58 by npiyapan         ###   ########.fr       */
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
	int				st;
	__uint64_t		eat_num;
	__uint64_t		start_time;
	pthread_mutex_t	mu_can_print;
	int				can_print;
	int				meals;
	pthread_mutex_t	mu_meals;
}	t_rule;

typedef struct s_philo
{
	__uint64_t		last_meal;
	int				name;
	struct s_rule	*rule;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_t		thds;
	pthread_t		monitor_thds;
}	t_philo;

void			init_r_fork(t_philo *p);
void			prnt_msg(t_philo *philo, char *s);
void			ft_usleep(__uint64_t ms);
void			*ft_action(void *p);
void			*ft_monitor(void *p);

int				check_input(int argc, char **argv);
int				handle_errors(char *error_msg);
int				ft_atoi(const char *str);
int				init_rule(t_rule *rule, int argc, char **argv);
int				init_philo(t_philo **philo, t_rule *rule);
int				init_threads(t_philo *philo);
int				get_alive_time(__uint64_t start_time);
int				check_eat_num(u_int64_t i, t_philo *philo);
int				check_can_print(t_philo *philo);

__uint64_t		get_time(void);

size_t			ft_strlen(const char *s);

void			monitor_loop(t_philo *p, t_rule *p_rule);
void			unlock_forks(t_philo *philo);
void			inc_meals(t_philo *philo);

int				join_threads(t_philo *philo, int num);
int				wait_meals(t_philo *philo);
