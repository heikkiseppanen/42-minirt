/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:04:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 09:52:32 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float3	ft_float3_add(t_float3 l, t_float3 r)
{
	return ((t_float3){l.x + r.x, l.y + r.y, l.z + r.z});
}

t_float3	ft_float3_sub(t_float3 l, t_float3 r)
{
	return ((t_float3){l.x - r.x, l.y - r.y, l.z - r.z});
}

t_float3	ft_float3_scalar(t_float3 l, float multiplier)
{
	return ((t_float3){l.x * multiplier, l.y * multiplier, l.z * multiplier});
}

t_float3	ft_float3_lerp(t_float3 start, t_float3 end, float factor)
{
	return ((t_float3){
		ft_lerp(start.x, end.x, factor),
		ft_lerp(start.y, end.y, factor),
		ft_lerp(start.z, end.z, factor)
	});
}

float	ft_float3_len(t_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
