/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:00 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/30 00:23:03 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
		if (av[i][j] == '+' && av[i][j + 1])
			j++;
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

long long	gettime_millisec(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("gettimeofday failed!");
		return (-1);
	}
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}

void	custom_usleep(unsigned long long time)
{
	long long	start;

	start = gettime_millisec();
	if (start == -1)
		return ;
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