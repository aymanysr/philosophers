/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:42:08 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/22 06:36:04 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	philos_allocation(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].left_fork = malloc(sizeof(pthread_mutex_t));
		if (!data->philos[i].left_fork)
			return (-1);
		i++;
	}
	return (0);
}

int	data_initialization(t_data *data, int ac, char **av)
{
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->kill_all = false;
	data->must_eat = -1;
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 0)
			return (-1);
	}
	if ((data->philo_nb <= 0 || data->philo_nb > 200) || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (-1);
	return (0);
}

void	forks_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(data->philos[i].left_fork, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->kill_all_mutex, NULL);
	pthread_mutex_init(&data->start_time_mutex, NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].right_fork = data->philos[(i + 1)
			% data->philo_nb].left_fork;
		i++;
	}
}

void	philos_initialization(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].has_finished_eating = false;
		data->philos[i].has_thought_once = false;
		pthread_mutex_init(&data->philos[i].meals_eaten_mutex, NULL);
		pthread_mutex_init(&data->philos[i].finish_eating_mutex, NULL);
		pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philos[i].has_thought_mutex, NULL);
		i++;
	}
}

int	main_initialization(t_data *data, int ac, char **av)
{
	if (data_initialization(data, ac, av))
		return (printf("error in data initializaton\n"), 1);
	if (philos_allocation(data))
		return (printf("error in philos allocation\n"), 1);
	forks_initialization(data);
	philos_initialization(data);
	return (0);
}
