/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:15:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/25 20:39:51 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int destroy_mutex(t_program * program)
{
    size_t i;

    i = 0;
    while (i < program->info.nb)
    {
        if(pthread_mutex_destroy(&program->fork[i]))
            return (ERROR);
        ++i;
    }
    return (SUCCESS);
}

int kill_all(t_program * program)
{
    destroy_mutex(program);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->dead_lock);
    free(program->fork);
    free(program->philos);
    return (SUCCESS);
}
