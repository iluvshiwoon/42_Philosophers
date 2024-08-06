/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:27:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:40:23 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void increment_active(t_philo * philo)
{
    pthread_mutex_lock(philo->lock_program);  
    (*philo->active_philo)++;
    pthread_mutex_unlock(philo->lock_program);
}

void *routine(void * data)
{
    t_philo * philo;

    philo = data;
    sync_thread(philo);
    desync(philo);
    set_long(&philo->lock_philo,&philo->last_meal,gettime(MILLISECOND));
    increment_active(philo);
    while (!get_bool(philo->lock_program, philo->end_program))
    {
        if (get_bool(&philo->lock_philo, &philo->full))
            break;
        eat(philo);
        write_status(SLEEPING, philo);
        ft_usleep(philo->info.t_sleep,philo);
        think(philo,false);
        usleep(1e3);
    }
    return (data);
}

int start_simu(t_program * program)
{
    int i;
    pthread_t monitor;

    i = -1;
    if (program->info.nb_philo == 1)
        i = 0; //
    else 
    {
        while (++i < program->info.nb_philo)
            print_error_mutex(pthread_create(&program->philos[i].thread_id,NULL, routine, &program->philos[i]));
    }
    program->program_start = gettime(MILLISECOND);
    print_error_mutex(pthread_create(&monitor,NULL,referee ,program));
    set_bool(&program->lock_program,&program->simu_ready,true);
    i = -1;
    while(++i < program->info.nb_philo)
        print_error_mutex(pthread_join(program->philos[i].thread_id,NULL));
    set_bool(&program->lock_program, &program->end_program, true);
    print_error_mutex(pthread_join(monitor,NULL));
    return (EXIT_SUCCESS);
}
