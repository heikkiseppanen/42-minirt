/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float4x4_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:09:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/20 13:25:19 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float4x4	ft_float4x4_translation(t_float3 pos)
{
	t_float4x4	translation;

	translation.a = (t_float4){1.0, 0.0, 0.0, pos.x};
	translation.b = (t_float4){0.0, 1.0, 0.0, pos.y};
	translation.c = (t_float4){0.0, 0.0, 1.0, pos.z};
	translation.d = (t_float4){0.0, 0.0, 0.0, 1.0};
	return (translation);
}

t_float4x4	ft_float4x4_rotation(t_float3 rot)
{
	const t_float3	cos = {cosf(rot.x), cosf(rot.y), cosf(rot.z)};
	const t_float3	sin = {sinf(rot.x), sinf(rot.y), sinf(rot.z)};
	t_float4x4		rotation;

	rotation.a.x = cos.y * cos.z;
	rotation.a.y = sin.x * sin.y * cos.z - cos.x * sin.z;
	rotation.a.z = cos.x * sin.y * cos.z + sin.x * sin.z;
	rotation.a.w = 0;
	rotation.b.x = cos.y * sin.z;
	rotation.b.y = sin.x * sin.y * sin.z + cos.x * cos.z;
	rotation.b.z = cos.x * sin.y * sin.z - sin.x * cos.z;
	rotation.b.w = 0;
	rotation.c.x = -sin.y;
	rotation.c.y = sin.x * cos.y;
	rotation.c.z = cos.x * cos.y;
	rotation.c.w = 0;
	rotation.d = (t_float4){0, 0, 0, 1};
	return (rotation);
}

t_float4x4	ft_float4x4_scaling(t_float3 scale)
{
	t_float4x4	scaling;

	scaling.a = (t_float4){scale.x, 0.0, 0.0, 0.0};
	scaling.b = (t_float4){0.0, scale.y, 0.0, 0.0};
	scaling.c = (t_float4){0.0, 0.0, scale.z, 0.0};
	scaling.d = (t_float4){0.0, 0.0, 0.0, 1.0};
	return (scaling);
}

t_float4x4	ft_float4x4_transpose(t_float4x4 *mat)
{
	return ((t_float4x4){
		{mat->a.x, mat->b.x, mat->c.x, mat->d.x},
		{mat->a.y, mat->b.y, mat->c.y, mat->d.y},
		{mat->a.z, mat->b.z, mat->c.z, mat->d.z},
		{mat->a.w, mat->b.w, mat->c.w, mat->d.w},
	});
}
