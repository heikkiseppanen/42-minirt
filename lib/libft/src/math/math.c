/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:02:06 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 09:12:36 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

float	ft_lerp(float start, float end, float factor)
{
	return ((1 - factor) * start + factor * end);
}

float	ft_clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	ft_rad(float deg)
{
	return (deg * (M_PI / 180));
}

float	ft_deg(float rad)
{
	return (rad * (180 / M_PI));
}
