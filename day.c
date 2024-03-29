/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:18:15 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/26 14:37:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo * philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*(philo->dead))
        return (pthread_mutex_unlock(philo->dead_lock),1);
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}

void message(t_philo * philo,char c)
{
    size_t time;

    time = get_current_time() - philo->start_time;
    pthread_mutex_lock(philo->write_lock);
    if (is_dead(philo))
    {
        pthread_mutex_unlock(philo->write_lock);
        return;
    }
    if (c == 'f')
        printf("%zu %d %s\n",time,philo->id,"has taken a fork");
    else if (c == 'e')
        printf("%zu %d %s\n",time,philo->id,"eating");
    else if (c == 's')
        printf("%zu %d %s\n",time,philo->id,"sleeping");
    else if (c == 't')
        printf("%zu %d %s\n",time,philo->id,"thinking");
    else if (c == 'd')
        printf("%zu %d %s\n",time,philo->id,"died");
    pthread_mutex_unlock(philo->write_lock);
}

void eating(t_philo * philo)
{
    pthread_mutex_lock(philo->r_fork);
    message(philo,'f');
    if (philo->info->nb == 1)
    {
        ft_usleep(philo->info->death_time);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    pthread_mutex_lock(philo->l_fork);
    message(philo,'f');
    message(philo, 'e');
    // pthread_mutex_lock(philo->dead_lock);
    philo->eating = 1;
    philo->last_meal = get_current_time();
    philo->meals_eaten += 1;
    ft_usleep(philo->info->eat_time);
    philo->eating = 0;
    // pthread_mutex_unlock(philo->dead_lock);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_philo * philo)
{
    message(philo,'s');
    ft_usleep(philo->info->sleep_time);
}

void thinking(t_philo * philo)
{
    message(philo, 't');
}

void *day(void * arg)
{
    t_philo * philo;
    philo = (t_philo *)arg;
    
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while(!is_dead(philo))
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (arg);
}
