/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <niran.analas@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:45:10 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/29 22:41:26 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int	get_forks(t_philo *philo)
{
	if (philo->rule->philo_num == 1)
	{
		ft_usleep(philo->rule->time_die + 10);
		return (1);
	}
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	prnt_msg(philo, "has taken a fork.");
	return (0);
}

static int	eating(t_philo *philo)
{
	prnt_msg(philo, "is eating.");
	ft_usleep(philo->rule->time_eat);
	pthread_mutex_lock(&philo->rule->mu_can_print);
	if (philo->rule->can_print == 0)
	{
		pthread_mutex_unlock(&philo->rule->mu_can_print);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->rule->mu_can_print);
	pthread_mutex_lock(&philo->mutex_last_meal);
	// if (get_alive_time(philo->last_meal) >= philo->rule->time_die)
	// {
	// 	pthread_mutex_unlock(&philo->mutex_last_meal);
	// 	prnt_msg(philo, "is die");
	// 	pthread_mutex_lock(&philo->rule->mu_can_print);
	// 	philo->rule->can_print = 0;
	// 	pthread_mutex_unlock(&philo->rule->mu_can_print);
	// 	pthread_mutex_unlock(&philo->l_fork);
	// 	pthread_mutex_unlock(philo->r_fork);
	// 	return (1);
	// }
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	prnt_msg(philo, "is sleeping.");
	ft_usleep(philo->rule->time_sleep);
	return (0);
}

void	*ft_action(void *p)
{
	t_philo		*philo;
	uint64_t	i;

	i = 0;
	philo = (t_philo *) p;
	pthread_mutex_lock (&philo->mutex_last_meal);
	philo->last_meal = get_time();
	philo->rule->start_time = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if ( (philo->name % 2) == 0)
		ft_usleep(philo->rule->time_sleep);
	while (i < philo->rule->eat_num)
	{
		get_forks(philo);
		if (eating(philo))
			break ;
		sleeping(philo);
		prnt_msg(philo, "is thinking.");
		i++;
	}
	prnt_msg(philo, "have eaten all of it.");
	pthread_mutex_lock(&philo->rule->mu_can_print);
	philo->rule->can_print = 0;
	pthread_mutex_unlock(&philo->rule->mu_can_print);
	return (NULL);
}

static int	join_thread(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].thds, NULL);
		i++;
	}
	pthread_join(philo[0].monitor_thds, NULL);
	return (0);
}

int main(int argc, char **argv)
{
	t_rule		rule;
	t_philo		*philo;
	pthread_t	*threads;
	int			i;

	check_input(argc, argv);
	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philo(&philo, &rule))
		return (1);
	if (init_threads(philo))
		return (1);
	join_thread(philo, rule.philo_num);
	free (philo);
	return (0);
}