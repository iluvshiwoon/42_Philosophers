/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:49:14 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/23 18:51:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_atoi(size_t * i, unsigned int * value, int * l_digit, int * sign)
{
    *i = 0;
    *value = 0;
    *l_digit = 7;
    *sign = 1;
    return;
}

int	ft_atoi_safe(char *string, int * status)
{
    size_t i;
    unsigned int value;
    int l_digit;
    int sign;

    if (init_atoi(&i, &value, &l_digit, &sign), string[0] == '-')
    {
        ++i;
        l_digit = 8;
        sign = -1;
    }
	while (string[i])
	{
        if (ft_isdigit(string[i]) && ((value == INT_MAX / 10 && string[i]
			- '0' > l_digit ) || (value > INT_MAX / 10)))
            return (*status = ERROR, 0);
        else if (ft_isdigit(string[i]))
			value = value * 10 + string[i] - '0';
        else
            return (*status = ERROR, 0);
        ++i;
	}
    if (value == (unsigned int){2147483648})
        return (*status = SUCCESS, INT_MIN);
    return (*status = SUCCESS, (int)value * sign);
}
