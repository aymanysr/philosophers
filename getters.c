/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:16 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/26 03:06:47 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>

long	get_start_time(t_philo *philo)
{
	long	start_time;

	pthread_mutex_lock(&philo->data->start_time_mutex);
	start_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->start_time_mutex);
	return (start_time);
}

long	get_last_meal(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (last_meal_time);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals_eaten;

	pthread_mutex_lock(&philo->meals_eaten_mutex);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (meals_eaten);
}

bool	get_finish_eating(t_philo *philo)
{
	bool	sign;

	pthread_mutex_lock(&philo->finish_eating_mutex);
	sign = philo->has_finished_eating;
	pthread_mutex_unlock(&philo->finish_eating_mutex);
	return (sign);
}

bool	get_kill_all(t_data *data)
{
	bool	sign;

	pthread_mutex_lock(&data->kill_all_mutex);
	sign = data->kill_all;
	pthread_mutex_unlock(&data->kill_all_mutex);
	return (sign);
}
