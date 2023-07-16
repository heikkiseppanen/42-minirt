/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:26:30 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/14 08:35:03 by hseppane         ###   ########.fr       */
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

t_float3	ft_float3_rot_axis(t_float3 l, t_float3 axis, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float4x4	matrix;

	matrix.a.x = dcos + (axis.x * axis.x * (1 - dcos));
	matrix.a.y = (axis.x * axis.y * (1 - dcos)) - (axis.z * dsin);
	matrix.a.z = (axis.x * axis.z * (1 - dcos)) + (axis.y * dsin);
	matrix.a.w = 0;
	matrix.b.x = (axis.y * axis.x * (1 - dcos)) + (axis.z * dsin);
	matrix.b.y = dcos + (axis.y * axis.y * (1 - dcos));
	matrix.b.z = (axis.y * axis.z * (1 - dcos)) - (axis.x * dsin);
	matrix.b.w = 0;
	matrix.c.x = (axis.z * axis.x * (1 - dcos)) - (axis.y * dsin);
	matrix.c.y = (axis.z * axis.y * (1 - dcos)) + (axis.x * dsin);
	matrix.c.z = dcos + (axis.z * axis.z * (1 - dcos));
	matrix.c.w = 0;
	matrix.d = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
	return (ft_float3_transform(&matrix, l));
}
