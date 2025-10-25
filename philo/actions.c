/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_eating(t_philo *philo)
{
	get_adjacent_forks(philo);
	print_message(EATING, philo);
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = ft_gettimestamp();
	philo->eat_count++;
	philo->eat_time = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	get_adjacent_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(TAKE_FORK, philo);
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKE_FORK, philo);
}

void	set_thinking(t_philo *philo)
{
	print_message(THINKING, philo);
}

void	set_sleeping(t_philo *philo)
{
	print_message(SLEEPING, philo);
	usleep(philo->sleep_time * 1000);
}

void	single_case(int death_time)
{
	long long	start;

	start = ft_gettimestamp();
	printf("0 0 %s\n", TAKE_FORK);
	usleep(death_time * 1000);
	printf("%lld 0 %s\n", ft_gettimestamp() - start, DIED);
}
