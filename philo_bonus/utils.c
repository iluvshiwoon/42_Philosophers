/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:50:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/30 17:40:08 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void destroy_sema(t_program * program)
{
    sem_close(program->info.fork);
    sem_close(program->info.death);
    sem_close(program->info.write);
    sem_unlink("fork");
    sem_unlink("death");
    sem_unlink("write");
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (SUCCESS);
}

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return(printf("gettimeofday() error\n"), 0);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

