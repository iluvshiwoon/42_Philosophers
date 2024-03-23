/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:52:07 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/23 19:11:22 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef enum e_signal {
    ERROR = 0,
    SUCCESS,
} t_signal;

typedef struct s_philo {
    int nb;
    int death_time;
    int eat_time;
    int sleep_time;
    int eat_nb;
} t_philo;

//utils
int	ft_isdigit(int c);
int	ft_atoi_safe(char *string, int * status);

#endif
