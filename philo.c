/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:49:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/24 19:34:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_input(int argc,char ** argv, t_program * program)
{
    int status;

    program->info.nb = ft_atoi_safe(argv[1],&status);
    if (!((program->info.nb > 0 && program->info.nb <= 200)) || !status)
        return (printf("Error\n"),ERROR);
    program->info.death_time = ft_atoi_safe(argv[2],&status);
        if (!(program->info.death_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    program->info.eat_time = ft_atoi_safe(argv[3],&status);
        if (!(program->info.eat_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    program->info.sleep_time = ft_atoi_safe(argv[4],&status);
        if (!(program->info.sleep_time > 0) || !status)
            return (printf("Error\n"),ERROR);
    if (argc == 6)
    {
        program->info.eat_nb = ft_atoi_safe(argv[5],&status);
            if (!(program->info.eat_nb >= 0) || !status)
                return (printf("Error\n"),ERROR);
    }
    else
        program->info.eat_nb = 0;
    return SUCCESS;
}

int main (int argc, char ** argv)
{
    t_program program;
    if (argc == 5 || argc == 6)
        parse_input(argc, argv, &program);
    else
        return(printf("Error\n"),ERROR);
    printf("%d %d %d %d", program.info.nb,program.info.death_time,program.info.eat_time, program.info.sleep_time);
    if (argc == 6)
        printf(" %d\n",program.info.eat_nb);
    else
        printf("\n");
    return SUCCESS;
}
