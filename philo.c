/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:49:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/09 14:22:18 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int argc, char ** argv)
{
    t_program program;
	int status;

    // argc = 5;
    // argv[1] = "1";
    // argv[2] = "800";
    // argv[3] = "200";
    // argv[4] = "200";
    if (argc == 5 || argc == 6)
        status = parse_input(argc, argv, &program);
    else
        return(printf("Error\n"),ERROR);
    printf("%d %d %d %d", program.info.nb,program.info.death_time,program.info.eat_time, program.info.sleep_time);
    if (argc == 6)
        printf(" %d\n",program.info.eat_nb);
    else
        printf("\n");
	if (status == ERROR)
		return (ERROR);
    init(&program);
    init_fork(&program);
    deal(&program);
    thread_create_all(&program);
    return SUCCESS;
}
