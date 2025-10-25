/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philos)
	{
		if (should_die(&philos[i], philos[i].death_time))
		{
			print_message(DIED, philos);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		pthread_mutex_lock(philos[0].dead_lock);
		if (*philos->dead == 1)
		{
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philos[0].dead_lock);
		i++;
	}
	return (0);
}

int	has_died(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	has_enough_eat(t_philo *philos)
{
	int	i;
	int	target;

	i = 0;
	target = 0;
	while (i < philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].eat_count >= philos[i].nb_to_eat
			&& philos[i].nb_to_eat != -1)
			target++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (philos[0].nb_philos == target)
	{	
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
