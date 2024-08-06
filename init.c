/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:34:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:40:27 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_program * program)
{
    int i;

    i = -1;
    while (++i < program->info.nb_philo)
    {
        if(print_error_mutex(pthread_mutex_init(&(program->forks[i].mtx),NULL)))
            return(destroy_forks(program->forks,i), EXIT_FAILURE);
        program->forks[i].id = i;
    }
    return(EXIT_SUCCESS);
}

void deal_forks(t_program * program, int i)
{    
    program->philos[i].second_fork = &program->forks[i];
    program->philos[i].first_fork = &program->forks[(i+1)%program->info.nb_philo];
    if (i % 2 == 0)
    {
        program->philos[i].first_fork = &program->forks[i];
        program->philos[i].second_fork = &program->forks[(i+1)%program->info.nb_philo];
    }
}

int init_philos(t_program * program)
{
    int i;

    i = -1;
    while (++i < program->info.nb_philo)
    {
        program->philos[i].info = program->info;
        program->philos[i].id = i + 1;
        program->philos[i].full = false;
        program->philos[i].meals_eaten = 0;
        program->philos[i].program_start = &program->program_start;
        program->philos[i].end_program = &program->end_program;
        program->philos[i].active_philo = &program->active_philo;
        program->philos[i].simu_ready = &program->simu_ready;
        program->philos[i].lock_program = &program->lock_program;
        program->philos[i].lock_write = &program->lock_write;
        if (print_error_mutex(pthread_mutex_init(&program->philos[i].lock_philo,NULL)))
            return(EXIT_FAILURE);
        deal_forks(program,i);
    }
    return(EXIT_SUCCESS);
}

int init(t_program * program, int argc, char ** argv)
{
    if(fill_info(&program->info, argc, argv))
        return(EXIT_FAILURE);
    program->end_program = false;
    program->active_philo = 0;
    program->simu_ready = false;
    program->philos = safe_malloc(sizeof(*program->philos)*program->info.nb_philo);
    program->forks = safe_malloc(sizeof(*program->forks)*program->info.nb_philo);
    if (print_error_mutex(pthread_mutex_init(&program->lock_program, NULL)))
        return (EXIT_FAILURE);
    if (print_error_mutex(pthread_mutex_init(&program->lock_write, NULL)))
        return (EXIT_FAILURE);
    if (!program->philos || !program->forks)
        return (free(program->forks),free(program->philos), EXIT_FAILURE);
    if(init_forks(program))
        return(EXIT_FAILURE);
    if(init_philos(program))
        return(EXIT_FAILURE);
    return(EXIT_SUCCESS);
}
