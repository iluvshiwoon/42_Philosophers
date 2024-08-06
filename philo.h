/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:52:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:23:12 by kgriset          ###   ########.fr       */
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
# include <stdbool.h>
# include <errno.h>

//ANSI ESCAPE
#define RESET "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    FIRST_FORK,
    SECOND_FORK,
    DIED,
} t_status;

typedef enum e_code
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    DETACH,
    JOIN
} t_code;

typedef enum e_time
{
    SECOND,
    MILLISECOND,
    MICROSECOND
} t_time;

typedef struct s_fork {
    pthread_mutex_t mtx;
    int             id;
} t_fork;

typedef struct s_info
{
	long				nb_philo;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				meals_limit;
}					t_info;

typedef struct s_philo
{
	long				id;
	long				meals_eaten;
	long			last_meal;
    long            *program_start;
    bool            full;
    bool            *end_program;
    bool            *simu_ready;
    long            *active_philo;
	t_info			info;
	t_fork	*first_fork;
	t_fork	*second_fork;
    pthread_mutex_t * lock_program;
    pthread_mutex_t * lock_write;
    pthread_mutex_t lock_philo;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_program
{
	long			program_start;
    long            active_philo;
    t_info          info;
	t_philo			*philos;
	t_fork	*forks;
    bool            end_program;
    bool            simu_ready;
    pthread_mutex_t lock_program;
    pthread_mutex_t lock_write;
}					t_program;

// sim.c
void *routine(void * data);
int start_simu(t_program * program);

// sync.c
void sync_thread(t_philo * philo);
void desync(t_philo * philo);

// monitor.c
void * referee(void * data);
bool philo_died(t_philo * philo);

// init.c
int init_forks(t_program * program);
void deal_forks(t_program * program, int i);
int init_philos(t_program * program);
int init(t_program * program, int argc, char ** argv);

// init_utils.c
int check_info(t_info * info);
int assign_info (long * info, char * str);
int fill_info(t_info * info, int argc, char ** argv);

// ft_atoi_safe.c
int	ft_atoi_safe(char *string, int *status);

// utils.c 
int error_return(const char * str);
void write_status(t_status status, t_philo * philo);
int print_error_mutex(int error_code);
void * safe_malloc(size_t bytes);

// time.c
long gettime(t_time code);
void ft_usleep(long usec, t_philo * philo);

// atomic.c
void set_bool(pthread_mutex_t * mtx, bool * data, bool value);
bool get_bool(pthread_mutex_t * mtx, bool * data);
void set_long(pthread_mutex_t * mtx, long * data, long value);
long get_long(pthread_mutex_t * mtx, long * data);

// actions.c
void think(t_philo * philo,bool pre_sim);
void eat(t_philo * philo);

// clean.c 
void destroy_forks(t_fork * forks, int i);

#endif
