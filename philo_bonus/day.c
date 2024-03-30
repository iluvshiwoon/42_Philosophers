/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:18:15 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/30 18:56:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void message(t_philo * philo,char c)
{
    size_t time;

    time = get_current_time() - philo->start_time;
    sem_wait(philo->info->write);
    if (philo->dead)
    {
        sem_post(philo->info->write);
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
    sem_post(philo->info->write);
}

void eating(t_philo * philo)
{
    sem_wait(philo->info->fork);
    message(philo,'f');
    if (philo->info->nb == 1)
    {
        ft_usleep(philo->info->death_time);
        sem_post(philo->info->fork);
        return;
    }
    sem_wait(philo->info->fork);
    philo->eating = 1;
    philo->meals_eaten += 1;
    message(philo,'f');
    message(philo, 'e');
    philo->last_meal = get_current_time();
    ft_usleep(philo->info->eat_time);
    philo->eating = 0;
    sem_post(philo->info->fork);
    sem_post(philo->info->fork);
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

void day(t_program * program, int i)
{
    t_philo philo;

    philo.var = program;
    philo.id = i + 1;
    philo.dead = 0;
    philo.eating = 0;
    philo.info = &program->info;
    philo.start_time = get_current_time();
    philo.last_meal = philo.start_time;
    philo.meals_eaten = 0;
    pthread_create(&philo.thread, NULL, &monitor, &philo);
    if (philo.id % 2 == 0)
        ft_usleep(1);
    while(!philo.dead && philo.meals_eaten != philo.info->eat_nb)
    {
        eating(&philo);
        sleeping(&philo);
        thinking(&philo);
    }
    pthread_detach(philo.thread);
}
