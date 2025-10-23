/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:04:22 by hkonte          #+#    #+#             */
/*   Updated: 2025/10/24 11:29:49 by hkonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef unsigned long long	t_ull;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				eating;
	t_ull			time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*threads;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	t_ull			death_time;
	t_ull			eat_time;
	t_ull			sleep_time;
	t_ull			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
void		print_message(char *str, t_philo *philo);
int			ft_exit(t_data *data);
t_ull		ft_gettime(void);
int			ft_usleep(t_ull time);
int			init(t_data *data, char **argv, int argc);
int			init_thread(t_data *data);
int			input_checker(char **argv);
void		eat(t_philo *philo);
void		*routine(void *philo_pointer);
#endif