/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
	{
		if (check_philos(philos) || has_enough_eat(philos))
			break ;
		usleep(50);
	}
	return (ptr);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(15000);
	while (!has_died(philo))
	{
		set_eating(philo);
		set_thinking(philo);
		set_sleeping(philo);
	}
	return (NULL);
}

void	clear_mutexes(int i, t_data *data, pthread_mutex_t *forks)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (data->philos[j].thread)
			pthread_join(data->philos[j].thread, NULL);
	}
	j = -1;
	while (++j < data->philos[0].nb_philos)
	{
		pthread_mutex_destroy(&forks[j]);
	}
}

void	init_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	thread_monitor;
	int			i;

	i = 0;
	while (i < data->philos[0].nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]) != 0)
		{
			clear_mutexes(i, data, forks);
			return ;
		}
		i++;
	}
	if (pthread_create(&thread_monitor, NULL, &monitor, data->philos) != 0)
	{
		clear_mutexes(i, data, forks);
		return ;
	}
	pthread_join(thread_monitor, NULL);
	i = 0;
	while (i < data->philos[0].nb_philos)
		pthread_join(data->philos[i++].thread, NULL);
}

int	should_die(t_philo *philo, long long time_to_die)
{
	long long	current_time;
	long long	time_since_last_meal;

	pthread_mutex_lock(philo->meal_lock);
	current_time = ft_gettimestamp();
	time_since_last_meal = current_time - philo->last_meal;
	if (time_since_last_meal > time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}
