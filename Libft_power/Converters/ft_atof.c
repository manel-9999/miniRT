/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:57:29 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/11/10 17:26:36 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

float	push_pointer(char **str)
{
	float	sign;

	sign = 1.0f;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1.0f;
		(*str)++;
	}
	return (sign);
}

void	calc_result(float *res, const char *str, int seen_dot, float *div)
{
	if (!seen_dot)
		*res = *res * 10.0f + (*str - '0');
	else
	{
		*div *= 10.0f;
		*res = *res + (*str - '0') / *div;
	}
}

float	ft_atof(char *str)
{
	float	result;
	float	sign;
	float	divisor;
	int		seen_dot;

	result = 0.0f;
	sign = push_pointer(&str);
	divisor = 1.0f;
	seen_dot = 0;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			seen_dot = 1;
			str++;
			continue ;
		}
		calc_result(&result, str, seen_dot, &divisor);
		str++;
	}
	return (result * sign);
}
