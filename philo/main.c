/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 \
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0 \
		|| (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		printf("%s\n", ERROR_BAD_INPUT);
		return (0);
	}
	return (1);
}

static int	init_data(t_data *data, t_philo **philos, pthread_mutex_t **forks, \
	int philo_id)
{
	*philos = malloc(sizeof(t_philo) * philo_id);
	*forks = malloc(sizeof(pthread_mutex_t) * philo_id);
	if (!(*philos) || !(*forks))
		return (0);
	init_mutexes(data, *philos);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data				data;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					philo_count;

	if (!check_args(argc, argv))
		return (printf("%s\n", ERROR_USAGE), 1);
	philo_count = ft_atoi(argv[1]);
	if (!init_data(&data, &philos, &forks, philo_count))
		return (printf("%s\n", ERROR_MALLOC), 1);
	if (philo_count == 1)
		single_case(ft_atoi(argv[2]));
	else
	{
		init_forks(forks, philo_count);
		init_philos(philos, &data, forks, argv);
		init_threads(&data, forks);
	}
	free(philos);
	free(forks);
	return (0);
}
