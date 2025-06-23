/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:24:28 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/19 18:24:46 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->data->philo_nb == 1)
	{
		thread_safe_print(philo, "has taken a fork");
		custom_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		philo_thinks(philo);
	while (!get_kill_all(philo->data) && (philo->data->must_eat == -1
			|| get_meals_eaten(philo) < philo->data->must_eat))
	{
		philo_eats(philo);
		if (philo->data->must_eat != -1
			&& get_meals_eaten(philo) >= philo->data->must_eat)
			break ;
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}

int	philo_lifecycle(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = gettime_millisec();
	while (i < data->philo_nb)
	{
		set_last_meal(&data->philos[i]);
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
		{
			perror("Failed to create philosopher thread");
			return (1);
		}
		usleep(20);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (printf("error in data initialization\n"), 1);
	if (check_input(av))
		return (1);
	if (main_initialization(data, ac, av))
		return (1);
	if (philo_lifecycle(data))
		return (1);
	monitor(data);
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(data->philos[i].left_fork);
		free(data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].meals_eaten_mutex);
		pthread_mutex_destroy(&data->philos[i].finish_eating_mutex);
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philos[i].has_thought_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->kill_all_mutex);
	pthread_mutex_destroy(&data->start_time_mutex);
	free(data->philos);
	free(data);
	return (0);
}
