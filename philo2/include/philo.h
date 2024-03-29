/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <niran.analas@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:46 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/29 23:22:57 by npiyapan         ###   ########.fr       */
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
	long long		eat_num;
	uint64_t		start_time;
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
	pthread_t		thds;
	pthread_t		monitor_thds;
}	t_philo;

void			check_input(int argc, char **argv);
void			handle_errors(char *error_msg);
void			init_r_fork(t_philo *p);
void			prnt_msg(t_philo *philo, char *s);
void			ft_usleep(uint64_t ms);

void			*ft_action(void *p);
void			*ft_monitor(void *p);

int				ft_atoi(const char *str);
int				init_rule(t_rule *rule, int argc, char **argv);
int				init_philo(t_philo **philo, t_rule *rule);
int				init_threads(t_philo *philo);
int				get_alive_time(uint64_t start_time);

uint64_t		get_time(void);

size_t			ft_strlen(const char *s);

static void		monitor_loop(t_philo *p, t_rule *p_rule);

int				join_threads(t_philo *philo, int num);
