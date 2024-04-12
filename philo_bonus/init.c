/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:14:40 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/12 09:50:07 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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


int init(t_program * program)
{
    sem_unlink("fork");
    sem_unlink("write");
    sem_unlink("death");
    program->info.fork = sem_open("fork", O_CREAT, 0700, program->info.nb);
    program->info.write = sem_open("write", O_CREAT, 0700, 1);
    program->info.death = sem_open("death", O_CREAT, 0700, 1);
    if (program->info.fork == SEM_FAILED || program->info.write == SEM_FAILED
    || program->info.death == SEM_FAILED)
        return (destroy_sema(program),ERROR);
    return (SUCCESS);
}

void create_process(t_program * program)
{
    size_t i;

    i = 0;
    while (i < program->info.nb)
    {
        program->pid[i] = fork();
        if (program->pid[i] == 0)
            day(program, i);    
        ++i;
    }
}

void kill_processes(t_program * program)
{
    size_t i;

    i = 0;
    while (i < program->info.nb)
    {
        kill(program->pid[i], SIGINT);
        ++i;
    }
}

int deal(t_program * program)
{
    size_t i;

    i = 0;
    program->pid = malloc(sizeof(*program->pid) * program->info.nb);
    if (!program->pid)
        return (destroy_sema(program),ERROR);
    program->info.start_time = get_current_time();
    create_process(program);
    while (i < program->info.nb)
    {
        waitpid(program->pid[i], 0, 0);
        ++i;
    }
    kill_processes(program);
    destroy_sema(program);
    return (free(program->pid),SUCCESS);
}
