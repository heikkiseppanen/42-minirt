/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:26:30 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 09:49:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float3	ft_float3_rot_x(t_float3 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float3	result;

	result.x = l.x;
	result.y = (l.y * dcos) - (l.z * dsin);
	result.z = (l.y * dsin) + (l.z * dcos);
	return (result);
}

t_float3	ft_float3_rot_y(t_float3 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float3	result;

	result.x = (l.x * dcos) + (l.z * dsin);
	result.y = l.y;
	result.z = -(l.x * dsin) + (l.z * dcos);
	return (result);
}

t_float3	ft_float3_rot_z(t_float3 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float3	result;

	result.x = (l.x * dcos) - (l.y * dsin);
	result.y = (l.x * dsin) + (l.y * dcos);
	result.z = l.z;
	return (result);
}
