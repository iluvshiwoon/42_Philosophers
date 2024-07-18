/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:18:15 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/18 22:30:11 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	message(philo, 'f');
	if (philo->info->nb == 1)
	{
		ft_usleep(philo->info->death_time);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	message(philo, 'f');
	message(philo, 'e');
	philo->eating = 1;
	philo->last_meal = get_current_time();
	philo->meals_eaten += 1;
	ft_usleep(philo->info->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	message(philo, 's');
	ft_usleep(philo->info->sleep_time);
}

void	thinking(t_philo *philo)
{
	message(philo, 't');
}

void	*day(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->info->start_time + 2 * philo->info->nb)
		ft_usleep(1);
    if (philo->id % 2 == 0)
    {
        if (philo->id < philo->info->nb / 2)
		    ft_usleep(3);
        else
            ft_usleep(6);
    }
	while (!is_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}
