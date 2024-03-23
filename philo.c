/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:49:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/23 19:19:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_input(int argc,char ** argv,t_philo * philo)
{
    int status;

    philo->nb = ft_atoi_safe(argv[1],&status);
    if (!((philo->nb > 0 && philo->nb <= 200)) || !status)
        return (printf("Error\n"),ERROR);
    philo->death_time = ft_atoi_safe(argv[2],&status);
        if (!(philo->death_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    philo->eat_time = ft_atoi_safe(argv[3],&status);
        if (!(philo->eat_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    philo->sleep_time = ft_atoi_safe(argv[4],&status);
        if (!(philo->sleep_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    if (argc == 6)
    {
        philo->eat_nb = ft_atoi_safe(argv[5],&status);
            if (!(philo->eat_nb >= 0) || !status)
                return (printf("Error\n"),ERROR);
    }
    else
        philo->eat_nb = 0;
    return SUCCESS;
}

int main (int argc, char ** argv)
{
    t_philo philo;
    if (argc == 5 || argc == 6)
        parse_input(argc, argv, &philo);
    else
        return(printf("Error\n"),ERROR);
    printf("%d %d %d %d", philo.nb,philo.death_time,philo.eat_time, philo.sleep_time);
    if (argc == 6)
        printf(" %d\n",philo.eat_nb);
    else
        printf("\n");
    return SUCCESS;
}
