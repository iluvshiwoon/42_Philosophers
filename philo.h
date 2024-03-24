/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:52:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/24 19:31:54 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <threads.h>

typedef enum e_signal {
    ERROR = 0,
    SUCCESS,
} t_signal;

typedef struct s_info {
    int nb;
    int death_time;
    int eat_time;
    int sleep_time;
    int eat_nb;
} t_info;

typedef struct s_philosophers {
    pthread_t thread;
    int id;
    int eating;
    int meals_eaten;
    size_t last_meal;
    size_t start_time;
    int  *dead;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
} t_philosophers;

typedef struct s_program
{
    int died;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    t_philosophers *philos;
    t_info info;
} t_program;

//utils
int	ft_isdigit(int c);
int	ft_atoi_safe(char *string, int * status);
size_t get_current_time(void);
int	ft_usleep(size_t milliseconds);

#endif
