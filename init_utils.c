/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:46:10 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 15:51:37 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_info(t_info * info) 
{
    if (info->nb_philo <= 0)
        return(error_return("Number of philo must be >= 1"));
    if (info->t_eat < 60 || info->t_die < 60 || info->t_sleep < 60)
        return(error_return("Timestamps must be >= 60 ms"));
    if (info->meals_limit != -1 && info->meals_limit <= 0)
        return(error_return("Number of meals to eat is invalid"));
    return (EXIT_SUCCESS);
}

int assign_info (long * info, char * str)
{
    int status;

    if (ft_atoi_safe(str, &status), status == EXIT_SUCCESS)
        *info = ft_atoi_safe(str, &status);
    else
        return(error_return("One or more inputs are either not a number or cannot fit an INT."));
    return (EXIT_SUCCESS);
}

int fill_info(t_info * info, int argc, char ** argv)
{
    int status;
    int r_value[4];

    r_value[0] = assign_info(&info->nb_philo, argv[1]);
    r_value[1] = assign_info(&info->t_die, argv[2]);
    r_value[2] = assign_info(&info->t_eat, argv[3]);
    r_value[3] = assign_info(&info->t_sleep, argv[4]);
    if (r_value[0] || r_value[1] || r_value[2] || r_value[3])
        return (EXIT_FAILURE);
    info->meals_limit = -1;
    if (argc == 6)
        r_value[0] = assign_info(&info->meals_limit, argv[5]);
    r_value[1] = check_info(info);
    if (r_value[0] || r_value[1])
        return(EXIT_FAILURE);
    info->t_die *= 1e3;
    info->t_eat *= 1e3;
    info->t_sleep *= 1e3;
    return(EXIT_SUCCESS);
}
