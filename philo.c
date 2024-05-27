/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:49:36 by kgriset           #+#    #+#             */
/*   Updated: 2024/05/27 13:00:53 by kgriset          ###   ########.fr       */
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
		return (printf("Error\n"), ERROR);
	if (status == ERROR)
		return (ERROR);
	init(&program);
	init_fork(&program);
	deal(&program);
	thread_create_all(&program);
	return (SUCCESS);
}
