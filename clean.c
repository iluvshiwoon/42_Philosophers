/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:19:37 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:31:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_forks(t_fork * forks, int i)
{
    int j;

    j = -1;
    while(++j <= i)
        pthread_mutex_destroy(&(forks[i].mtx));
}


