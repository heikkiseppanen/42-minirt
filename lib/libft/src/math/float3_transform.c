/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:26:30 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/31 09:29:01 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float3	ft_float3_transform(const t_float4x4 *l, t_float3 r)
{
	t_float3	out;
	float		out_w;

	out.x = l->a.x * r.x + l->a.y * r.y + l->a.z * r.z + l->a.w;
	out.y = l->b.x * r.x + l->b.y * r.y + l->b.z * r.z + l->b.w;
	out.z = l->c.x * r.x + l->c.y * r.y + l->c.z * r.z + l->c.w;
	out_w = l->d.x * r.x + l->d.y * r.y + l->d.z * r.z + l->d.w;
	if (out_w != 1.0f)
	{
		out.x /= out_w;
		out.y /= out_w;
		out.z /= out_w;
	}
	return (out);
}

float	ft_float3_len(t_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_float3	ft_float3_normalize(t_float3 vector)
{
	const float	len = ft_float3_len(vector);

	vector.x /= len;
	vector.y /= len;
	vector.z /= len;
	return (vector);
}

t_float3	ft_float3_cross(t_float3 l, t_float3 r)
{
	return ((t_float3){
		l.y * r.z - l.z * r.y,
		l.z * r.x - l.x * r.z,
		l.x * r.y - l.y * r.x
	});
}

float	ft_float3_dot(t_float3 l, t_float3 r)
{
	return (l.x * r.x + l.y * r.y + l.z * r.z);
}
