/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:06 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/27 12:58:00 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_dead(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < program->info.nb)
	{
		if (get_current_time()
			- program->philos[i].last_meal >= program->info.death_time
			&& program->philos[i].eating == 0)
		{
			message(&program->philos[i], 'd');
			pthread_mutex_lock(program->philos[i].dead_lock);
			*(program->philos[i].dead) = 1;
			pthread_mutex_unlock(program->philos[i].dead_lock);
			return (1);
		}
		++i;
	}
	return (0);
}

int	check_all_ate(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < program->info.nb)
	{
		if (!program->info.eat_nb
			|| program->philos[i].meals_eaten < program->info.eat_nb)
			return (0);
		++i;
	}
	pthread_mutex_lock(program->philos[0].dead_lock);
	*(program->philos[0].dead) = 1;
	pthread_mutex_unlock(program->philos[0].dead_lock);
	return (1);
}

void	*monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (check_all_dead(program) || check_all_ate(program))
			break ;
	}
	return (arg);
}

int	thread_create_all(t_program *program)
{
	size_t		i;
	pthread_t	monitor_t;

	i = 0;
	if (pthread_create(&monitor_t, NULL, &monitor, program))
		return (kill_all(program), ERROR);
	while (i < program->info.nb)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &day,
				&program->philos[i]))
			return (kill_all(program), ERROR);
		++i;
	}
	i = 0;
	if (pthread_join(monitor_t, NULL))
		return (kill_all(program), ERROR);
	while (i < program->info.nb)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			return (kill_all(program), ERROR);
		++i;
	}
	return (kill_all(program), SUCCESS);
}
