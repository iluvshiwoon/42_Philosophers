/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:07:16 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:25:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sync_thread(t_philo * philo)
{
    while(get_bool(philo->lock_program, philo->simu_ready) == false)
        usleep(1e3);
}

void desync(t_philo * philo)
{
    if (philo->info.nb_philo % 2 == 0)
    {
        if (philo->id %2 == 0)
            ft_usleep(3e4,philo);
    }
    else
    {
        if (philo->id%2)
            think(philo,true);
    }
}
