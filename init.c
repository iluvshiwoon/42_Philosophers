/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:14:40 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 14:56:11 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(int argc, char **argv, t_program *program)
{
	int	status;

	program->info.nb = ft_atoi_safe(argv[1], &status);
	if (!((program->info.nb > 0 && program->info.nb <= 200)) || status == EXIT_FAILURE)
		return (printf("Error\n"), EXIT_FAILURE);
	program->info.death_time = ft_atoi_safe(argv[2], &status);
	if (!(program->info.death_time > 0) || status == EXIT_FAILURE)
		return (printf("Error\n"), EXIT_FAILURE);
	program->info.eat_time = ft_atoi_safe(argv[3], &status);
	if (!(program->info.eat_time > 0) || status == EXIT_FAILURE)
		return (printf("Error\n"), EXIT_FAILURE);
	program->info.sleep_time = ft_atoi_safe(argv[4], &status);
	if (!(program->info.sleep_time > 0) || status == EXIT_FAILURE)
		return (printf("Error\n"), EXIT_FAILURE);
	if (argc == 6)
	{
		program->info.eat_nb = ft_atoi_safe(argv[5], &status);
		if (!(program->info.eat_nb >= 0) || status == EXIT_FAILURE)
			return (printf("Error\n"), EXIT_FAILURE);
	}
	else
		program->info.eat_nb = 0;
	return (EXIT_SUCCESS);
}

int	init(t_program *program)
{
	program->fork = malloc(sizeof(*program->fork) * program->info.nb);
	program->philos = malloc(sizeof(*program->philos) * program->info.nb);
	program->died = 0;
	if (!program->fork || !program->philos)
		return (EXIT_FAILURE);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	return (EXIT_SUCCESS);
}

int	init_fork(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < program->info.nb)
	{
		if (pthread_mutex_init(&program->fork[i], NULL))
			return (kill_all(program), EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	deal(t_program *program)
{
	size_t	i;

	i = 0;
	program->info.start_time = get_current_time();
	while (i < program->info.nb)
	{
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].meals_eaten = 0;
		program->philos[i].start_time = get_current_time();
		program->philos[i].last_meal = program->philos[i].start_time;
		program->philos[i].dead = &program->died;
		program->philos[i].l_fork = &program->fork[i];
		if (i == 0)
			program->philos[i].r_fork = &program->fork[program->info.nb - 1];
		else
			program->philos[i].r_fork = &program->fork[i - 1];
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].info = &program->info;
		++i;
	}
	return (EXIT_SUCCESS);
}
