/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data,
pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].eating = 0;
		philos[i].death_time = (long long)ft_atoi(argv[2]);
		philos[i].eat_time = (long long)ft_atoi(argv[3]);
		philos[i].sleep_time = (long long)ft_atoi(argv[4]);
		philos[i].nb_philos = (long long)ft_atoi(argv[1]);
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].start_time = data->start_time;
		philos[i].last_meal = ft_gettimestamp();
		share_forks(argv, philos, i, forks);
		i++;
	}
}

void	share_forks(char **argv, t_philo *philos, int i, pthread_mutex_t *forks)
{
	pthread_mutex_t	*temp;

	if (argv[5])
		philos[i].nb_to_eat = ft_atoi(argv[5]);
	else
		philos[i].nb_to_eat = -1;
	if (i == 0)
		philos[i].r_fork = &forks[philos[i].nb_philos - 1];
	else
		philos[i].r_fork = &forks[i - 1];
	if (philos[i].l_fork > philos[i].r_fork)
	{
		temp = philos[i].l_fork;
		philos[i].l_fork = philos[i].r_fork;
		philos[i].r_fork = temp;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_mutexes(t_data *data, t_philo *philos)
{
	struct timeval	tv;

	data->dead_flag = 0;
	data->philos = philos;
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}
