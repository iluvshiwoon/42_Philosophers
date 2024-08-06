/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:35:05 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:40:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_bool(pthread_mutex_t * mtx, bool * data, bool value)
{
    pthread_mutex_lock(mtx);
    *data = value;
    pthread_mutex_unlock(mtx);
}

bool get_bool(pthread_mutex_t * mtx, bool * data)
{
    bool r_value;
    pthread_mutex_lock(mtx);
    r_value = *data;
    pthread_mutex_unlock(mtx);
    return (r_value);
}

void set_long(pthread_mutex_t * mtx, long * data, long value)
{
    pthread_mutex_lock(mtx);
    *data = value;
    pthread_mutex_unlock(mtx);
}

long get_long(pthread_mutex_t * mtx, long * data)
{
    long r_value;
    pthread_mutex_lock(mtx);
    r_value = *data;
    pthread_mutex_unlock(mtx);
    return (r_value);
}
