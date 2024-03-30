/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:52:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/30 17:31:42 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <wait.h>

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
    sem_t *fork;
    sem_t *death;
    sem_t *write;
    size_t start_time;
} t_info;

typedef struct s_program
{
    int * pid;
    t_info info;
} t_program;

typedef struct s_philo {
    pthread_t thread;
    int id;
    int eating;
    int meals_eaten;
    size_t last_meal;
    size_t start_time;
    int  dead;
    t_info * info;
    t_program * var;
} t_philo;


//// PHILO

// Init
int parse_input(int argc,char ** argv, t_program * program);
int init(t_program * program);
int deal(t_program * program);

// Processes
void day(t_program * program, int i);
void * monitor(void * arg);

// Utils
int	ft_isdigit(int c);
int	ft_atoi_safe(char *string, int * status);
size_t get_current_time(void);
int	ft_usleep(size_t milliseconds);
void message(t_philo * philo,char c);
void destroy_sema(t_program * program);
void kill_processes(t_program * program);

#endif
