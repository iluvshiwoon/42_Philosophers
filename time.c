/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:34:31 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:34:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long gettime(t_time code)
{
    struct timeval time;
    if(SECOND == code)
        return (gettimeofday(&time,NULL),time.tv_sec + time.tv_usec / 1e6);
    else if (MILLISECOND == code)
        return (gettimeofday(&time,NULL),time.tv_sec * 1e3 + time.tv_usec / 1e3);
    else if (MICROSECOND == code)
        return (gettimeofday(&time,NULL),time.tv_sec * 1e6 + time.tv_usec);
    else
        return(42);
}

void ft_usleep(long usec, t_philo * philo)
{
    long start;
    long rem;

    start = gettime(MICROSECOND);
    while(gettime(MICROSECOND) - start < usec)
    {
        if(get_bool(philo->lock_program, philo->end_program))
            break;
        rem = gettime(MICROSECOND) - start;
        if (rem / 2 > 1e3)
            usleep(rem / 2);
        else
            while(gettime(MICROSECOND) - start < usec);
    }
}
