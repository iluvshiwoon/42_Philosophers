/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:49:14 by kgriset           #+#    #+#             */
/*   Updated: 2024/07/19 14:57:04 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_atoi(size_t *i, unsigned int *value, int *l_digit, int *sign)
{
	*i = 0;
	*value = 0;
	*l_digit = 7;
	*sign = 1;
	return ;
}

int	ft_atoi_safe(char *string, int *status)
{
	size_t			i;
	unsigned int	value;
	int				l_digit;
	int				sign;

	if (init_atoi(&i, &value, &l_digit, &sign), string[0] == '-')
	{
		++i;
		l_digit = 8;
		sign = -1;
	}
	while (string[i])
	{
		if (ft_isdigit(string[i]) && ((value == INT_MAX / 10 && string[i]
					- '0' > l_digit) || (value > INT_MAX / 10)))
			return (*status = EXIT_FAILURE, 0);
		else if (ft_isdigit(string[i]))
			value = value * 10 + string[i] - '0';
		else
			return (*status = EXIT_FAILURE, 0);
		++i;
	}
	if (value == (unsigned int){2147483648})
		return (*status = EXIT_SUCCESS, INT_MIN);
	return (*status = EXIT_SUCCESS, (int)value * sign);
}
