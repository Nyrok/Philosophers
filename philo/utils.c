/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettimestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000LL) + (t.tv_usec / 1000LL));
}

void	print_message(char *suffix, t_philo *philo)
{
	long long	elapsed_time;

	elapsed_time = ft_gettimestamp() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (!has_died(philo))
		printf("%lld %d %s\n", elapsed_time, philo->id, suffix);
	pthread_mutex_unlock(philo->write_lock);
}
