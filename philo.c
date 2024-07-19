/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:49:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 14:58:05 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	program;
	int			status;

	if (argc == 5 || argc == 6)
		status = parse_input(argc, argv, &program);
	else
		return (printf("Error\n"), EXIT_FAILURE);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init(&program) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_fork(&program);
	deal(&program);
	thread_create_all(&program);
	return (EXIT_SUCCESS);
}
