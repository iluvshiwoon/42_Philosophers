/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:38:21 by kgriset           #+#    #+#             */
/*   Updated: 2024/08/06 16:24:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char ** argv)
{
    t_program program;
    if (argc != 5 && argc != 6)
        return(error_return("Wrong number of arguments 🟥."BOLD_GREEN" try ./philo 5 800 200 200"));
    if(init(&program, argc, argv))
       return(EXIT_FAILURE);
    start_simu(&program);
    // for now
    destroy_forks(program.forks, program.info.nb_philo - 1);
    free(program.philos);
    free(program.forks);
    return(EXIT_SUCCESS);
}
