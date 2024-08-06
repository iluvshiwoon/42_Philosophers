/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:33:02 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:40:26 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo * philo,bool pre_sim)
{
    long t_think;
    if (!pre_sim)
        write_status(THINKING,philo);
    if (philo->info.nb_philo % 2 == 0)
        return;
    t_think = philo->info.t_eat * 2 - philo->info.t_sleep;
    if (think < 0)
        t_think = 0;
    ft_usleep(t_think * 0.42,philo);
}

void eat(t_philo * philo)
{
    pthread_mutex_lock(&philo->first_fork->mtx);
    write_status(FIRST_FORK,philo);
    pthread_mutex_lock(&philo->second_fork->mtx);
    write_status(SECOND_FORK,philo);

    set_long(&philo->lock_philo, &philo->last_meal, gettime(MILLISECOND));
    write_status(EATING, philo);
    philo->meals_eaten++;
    ft_usleep(philo->info.t_eat, philo);
    pthread_mutex_unlock(&philo->first_fork->mtx);
    pthread_mutex_unlock(&philo->second_fork->mtx);
    if (philo->info.meals_limit > 0 && philo->meals_eaten == philo->info.meals_limit)
        set_bool(&philo->lock_philo,&philo->full,true);
}
