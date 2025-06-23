/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:07 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/18 23:45:24 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void set_start_time(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->start_time_mutex);
//     philo->start_time = gettime_millisec();
//     pthread_mutex_unlock(&philo->start_time_mutex);
// }

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = gettime_millisec();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

void	set_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
}

void	set_finish_eating(t_philo *philo, bool sign)
{
	pthread_mutex_lock(&philo->finish_eating_mutex);
	philo->has_finished_eating = sign;
	pthread_mutex_unlock(&philo->finish_eating_mutex);
}

void	set_kill_all(t_data *data, bool sign)
{
	pthread_mutex_lock(&data->kill_all_mutex);
	data->kill_all = sign;
	pthread_mutex_unlock(&data->kill_all_mutex);
}

void	set_has_thought_once(t_philo *philo, bool sign)
{
	pthread_mutex_lock(&philo->has_thought_mutex);
	philo->has_thought_once = sign;
	pthread_mutex_unlock(&philo->has_thought_mutex);
}
