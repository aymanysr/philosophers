/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:00 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/22 07:03:28 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// #include <sys/time.h> // Include this header for gettimeofday function
long long	gettime_millisec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}

void	custom_usleep(unsigned long long time)
{
	long long	start;

	start = gettime_millisec();
	while (gettime_millisec() - start < (long long)time)
		usleep(50);
}

void	thread_safe_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (get_kill_all(philo->data) == false)
	{
		printf("%lld	%d	%s\n",
			(gettime_millisec() - get_start_time(philo)),
			philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	get_has_thought_once(t_philo *philo)
{
	bool	sign;

	pthread_mutex_lock(&philo->has_thought_mutex);
	sign = philo->has_thought_once;
	pthread_mutex_unlock(&philo->has_thought_mutex);
	return (sign);
}
