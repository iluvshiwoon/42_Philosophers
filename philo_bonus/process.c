/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:06 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/12 09:59:47 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void * monitor(void * arg)
{
    t_philo * philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (philo->meals_eaten == philo->info->eat_nb && philo->info->eat_nb)
        {
            philo->dead = 1;
            return (arg);
        }
        if (get_current_time() - philo->last_meal >= philo->info->death_time && !philo->eating)
        {
            sem_wait(philo->info->death);
            message(philo, 'd');
            philo->dead = 1; 
            kill_processes(philo->var);
            destroy_sema(philo->var);
            exit(1);
        }
        usleep(100);
    }
    return (arg);
}
