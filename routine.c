/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:22 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/26 03:05:36 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define SAFE_MARGIN 10

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	thread_safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	thread_safe_print(philo, "has taken a fork");
	set_last_meal(philo);
	thread_safe_print(philo, "is eating");
	custom_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->data->must_eat)
		set_finish_eating(philo, true);
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_thinks(t_philo *philo)
{
	int	max_think;
	int	desired_think;
	int	actual_think;

	desired_think = philo->data->time_to_eat;
	max_think = philo->data->time_to_die
		- philo->data->time_to_eat
		- philo->data->time_to_sleep
		- SAFE_MARGIN;
	if (max_think < 0)
		max_think = 0;
	actual_think = desired_think;
	if (actual_think > max_think)
		actual_think = max_think;
	thread_safe_print(philo, "is thinking");
	if (actual_think > 0)
		custom_usleep(actual_think);
}

void	philo_sleeps(t_philo *philo)
{
	thread_safe_print(philo, "is sleeping");
	custom_usleep(philo->data->time_to_sleep);
}
