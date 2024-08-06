/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:28:58 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:23:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
bool philo_died(t_philo * philo)
{
    long elapsed;

    if (get_bool(&philo->lock_philo, &philo->full))
        return(false);
    elapsed = gettime(MILLISECOND) - get_long(&philo->lock_philo, &philo->last_meal);
    if (elapsed >= philo->info.t_die / 1e3)
        return(true);
    return(false);
}
void * referee(void * data)
{
    t_program * program;
    int i;
    program = data;

    sync_thread(&program->philos[0]);
    while(get_long(&program->lock_program,&program->active_philo)!=program->info.nb_philo)
        usleep(1e3);
    while (!get_bool(&program->lock_program, &program->end_program))
    {
        i = -1;
        while(++i < program->info.nb_philo && !get_bool(&program->lock_program, &program->end_program))
        {
            if (philo_died(&program->philos[i]))
            {
                write_status(DIED, &program->philos[i]);
                set_bool(program->philos[i].lock_program,program->philos[i].end_program,true);
            }
        }
        usleep(1e3);
    }
    return(data);
}

