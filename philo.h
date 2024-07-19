/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:52:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 15:01:46 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				nb;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				eat_nb;
	size_t			start_time;
}					t_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	int				*dead;
	t_info			info;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				died;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*fork;
	t_info			info;
}					t_program;

//// PHILO

// Init
int					parse_input(int argc, char **argv, t_program *program);
int					init(t_program *program);
int					init_fork(t_program *program);
int					deal(t_program *program);

// Thread
void				*day(void *arg);
int					thread_create_all(t_program *program);

// End
int					kill_all(t_program *program);
int					destroy_mutex(t_program *program);

// Utils
int					is_dead(t_philo *philo);
int					ft_isdigit(int c);
int					ft_atoi_safe(char *string, int *status);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				message(t_philo *philo, char c);

#endif
