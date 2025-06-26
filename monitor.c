/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:24:09 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/26 00:48:34 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_finished_philos(t_data *data)
{
	int	i;
	int	finished_philos;

	i = 0;
	finished_philos = 0;
	while (i < data->philo_nb)
	{
		if (get_finish_eating(&data->philos[i]) == true)
			finished_philos++;
		i++;
	}
	return (finished_philos);
}

static bool	check_all_eaten(t_data *data)
{
	if (data->must_eat != -1
		&& check_finished_philos(data) >= data->philo_nb)
	{
		set_kill_all(data, true);
		return (true);
	}
	return (false);
}

static void	announce_death(t_data *data, int i)
{
	if (get_kill_all(data) == false)
	{
		set_kill_all(data, true);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld  %d died\n", gettime_millisec()
			- get_start_time(&data->philos[i]), data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

static bool	check_for_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (get_finish_eating(&data->philos[i]) == true)
		{
			i++;
			continue ;
		}
		if ((gettime_millisec()
				- get_last_meal(&data->philos[i]) > data->time_to_die))
		{
			announce_death(data, i);
			return (true);
		}
		i++;
	}
	return (false);
}

void	monitor(t_data *data)
{
	while (get_kill_all(data) == false)
	{
		if (check_all_eaten(data))
			break ;
		if (check_for_death(data))
			break ;
		usleep(200);
	}
}
