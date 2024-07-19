/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:50:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 14:57:11 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (EXIT_SUCCESS);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("gettimeofday() error\n"), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	message(t_philo *philo, char c)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	if (c == 'f')
		printf("%zu %d %s\n", time, philo->id, "has taken a fork");
	else if (c == 'e')
		printf("%zu %d %s\n", time, philo->id, "is eating");
	else if (c == 's')
		printf("%zu %d %s\n", time, philo->id, "is sleeping");
	else if (c == 't')
		printf("%zu %d %s\n", time, philo->id, "is thinking");
	else if (c == 'd')
		printf("%zu %d %s\n", time, philo->id, "died");
	pthread_mutex_unlock(philo->write_lock);
}
