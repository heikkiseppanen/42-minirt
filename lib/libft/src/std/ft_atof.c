/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:31:34 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/14 10:31:35 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/std.h"

#include "ft/cstr.h"

float	fraction(const char *str, int sign)
{
	double	fraction_result;
	int		divider;

	fraction_result = 0.0;
	divider = 1;
	while (ft_isdigit(*str))
	{
		fraction_result = fraction_result * 10 + (*str - '0') * sign;
		divider *= 10;
		str++;
	}
	return (fraction_result / divider);
}

float	ft_atof(const char *str)
{
	double	result;
	double	fraction_result;
	int		sign;

	sign = 1;
	result = 0.0;
	fraction_result = 0.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0') * sign;
		str++;
	}
	if (*str == '.')
		fraction_result = fraction(++str, sign);
	return (result + fraction_result);
}
