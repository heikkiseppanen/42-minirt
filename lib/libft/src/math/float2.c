/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:04:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 09:25:25 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float2	ft_float2_add(t_float2 l, t_float2 r)
{
	return ((t_float2){l.x + r.x, l.y + r.y});
}

t_float2	ft_float2_sub(t_float2 l, t_float2 r)
{
	return ((t_float2){l.x - r.x, l.y - r.y});
}

t_float2	ft_float2_scalar(t_float2 l, float multiplier)
{
	return ((t_float2){l.x * multiplier, l.y * multiplier});
}

t_float2	ft_float2_lerp(t_float2 start, t_float2 end, float factor)
{
	return ((t_float2){
		ft_lerp(start.x, end.x, factor),
		ft_lerp(start.y, end.y, factor)
	});
}

float	ft_float2_len(t_float2 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y));
}
