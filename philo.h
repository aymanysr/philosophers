/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayousr <ayousr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:30:46 by ayousr            #+#    #+#             */
/*   Updated: 2025/06/26 03:09:02 by ayousr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>

# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	pthread_t		thread;

	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;

	bool			has_finished_eating;
	pthread_mutex_t	finish_eating_mutex;

	long			last_meal;
	pthread_mutex_t	last_meal_mutex;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	bool			has_thought_once;
	pthread_mutex_t	has_thought_mutex;
}	t_philo;

typedef struct s_data
{
	pthread_t		td;		// Thread for monitoring
	int				philo_nb;	// Number of philosophers
	int				time_to_die; // Time until philosopher dies if not eating
	int				time_to_eat; // Time it takes to eat
	int				time_to_sleep; // Time it takes to sleep
	int				must_eat;	// Number of times each philosopher must eat
	bool			kill_all;	// Flag to terminate all threads
	pthread_mutex_t	kill_all_mutex; // Mutex to protect kill_all flag
	pthread_mutex_t	print_mutex; // Mutex for synchronized printing
	long			start_time;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	*forks;		// Array of mutexes representing forks
	t_philo			*philos;	// Array of philosopher structures
}	t_data;

int			data_initialization(t_data *data, int ac, char **av);
void		forks_initialization(t_data *data);
int			philos_allocation(t_data *data);
void		philos_initialization(t_data *data);
int			main_initialization(t_data *data, int ac, char **av);

void		philo_eats(t_philo *philo);
void		philo_thinks(t_philo *philo);
void		philo_sleeps(t_philo *philo);
int			philo_lifecycle(t_data *data);

int			check_finished_philos(t_data *data);
void		monitor(t_data *data);

int			check_input(char **av);
long long	gettime_millisec(void);
void		custom_usleep(unsigned long long time);
void		thread_safe_print(t_philo *philo, char *str);

void		set_start_time(t_philo *philo);
void		set_last_meal(t_philo *philo);
void		set_meals_eaten(t_philo *philo);
void		set_finish_eating(t_philo *philo, bool sign);
void		set_kill_all(t_data *data, bool sign);
void		set_has_thought_once(t_philo *philo, bool sign);

long		get_start_time(t_philo *philo);
long		get_last_meal(t_philo *philo);
bool		get_finish_eating(t_philo *philo);
int			get_meals_eaten(t_philo *philo);
bool		get_kill_all(t_data *data);
bool		get_has_thought_once(t_philo *philo);

int			ft_atoi(const char *str);
#endif