/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:56:39 by hkonte            #+#    #+#             */
/*   Updated: 2025/10/24 11:20:34 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_BAD_INPUT "Bad input!"
# define ERROR_USAGE "Usage: ./philo <nb_philos> <ttd> <tte> <tts> [nb_meals]"
# define ERROR_MALLOC "Memory allocation failed"

# define TAKE_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				eat_count;
	long long		last_meal;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	int				nb_philos;
	int				nb_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	long long		start_time;
	t_philo			*philos;
}					t_data;

int			ft_atoi(const char *nptr);
void		share_forks(char **argv, t_philo *philos, int i, \
	pthread_mutex_t *forks);
int			check_philos(t_philo *philos);
int			has_enough_eat(t_philo *philos);
int			has_died(t_philo *philo);
long long	ft_gettimestamp(void);
void		init_mutexes(t_data *data, t_philo *philos);
void		init_forks(pthread_mutex_t *forks, int philo_num);
void		init_philos(t_philo *philos, t_data *data,
				pthread_mutex_t *forks, char **argv);
void		init_threads(t_data *data, pthread_mutex_t *forks);
void		*routine(void *ptr);
int			should_die(t_philo *philo, long long time_to_die);
void		print_message(char *suffix, t_philo *philo);
void		set_sleeping(t_philo *philo);
void		set_thinking(t_philo *philo);
void		set_eating(t_philo *philo);
void		get_adjacent_forks(t_philo *philo);
void		single_case(int death_time);

#endif