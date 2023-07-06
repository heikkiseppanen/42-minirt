/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float4x4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:53:18 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 09:47:21 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float4x4	ft_float4x4_mul(const t_float4x4 *l, const t_float4x4 *r)
{
	const t_float4x4	result = {
	{l->a.x * r->a.x + l->a.y * r->b.x + l->a.z * r->c.x + l->a.w * r->d.x,
		l->a.x * r->a.y + l->a.y * r->b.y + l->a.z * r->c.y + l->a.w * r->d.y,
		l->a.x * r->a.z + l->a.y * r->b.z + l->a.z * r->c.z + l->a.w * r->d.z,
		l->a.x * r->a.w + l->a.y * r->b.w + l->a.z * r->c.w + l->a.w * r->d.w},
	{l->b.x * r->a.x + l->b.y * r->b.x + l->b.z * r->c.x + l->b.w * r->d.x,
		l->b.x * r->a.y + l->b.y * r->b.y + l->b.z * r->c.y + l->b.w * r->d.y,
		l->b.x * r->a.z + l->b.y * r->b.z + l->b.z * r->c.z + l->b.w * r->d.z,
		l->b.x * r->a.w + l->b.y * r->b.w + l->b.z * r->c.w + l->b.w * r->d.w},
	{l->c.x * r->a.x + l->c.y * r->b.x + l->c.z * r->c.x + l->c.w * r->d.x,
		l->c.x * r->a.y + l->c.y * r->b.y + l->c.z * r->c.y + l->c.w * r->d.y,
		l->c.x * r->a.z + l->c.y * r->b.z + l->c.z * r->c.z + l->c.w * r->d.z,
		l->c.x * r->a.w + l->c.y * r->b.w + l->c.z * r->c.w + l->c.w * r->d.w},
	{l->d.x * r->a.x + l->d.y * r->b.x + l->d.z * r->c.x + l->d.w * r->d.x,
		l->d.x * r->a.y + l->d.y * r->b.y + l->d.z * r->c.y + l->d.w * r->d.y,
		l->d.x * r->a.z + l->d.y * r->b.z + l->d.z * r->c.z + l->d.w * r->d.z,
		l->d.x * r->a.w + l->d.y * r->b.w + l->d.z * r->c.w + l->d.w * r->d.w}};

	return (result);
}

t_float4x4	ft_float4x4_ortho(float size, float aspect, float near, float far)
{
	t_float4x4		projection;

	projection.a.x = 1 / size * aspect;
	projection.a.y = 0.0;
	projection.a.z = 0.0;
	projection.a.w = 0.0;
	projection.b.x = 0.0;
	projection.b.y = 1 / size;
	projection.b.z = 0.0;
	projection.b.w = 0.0;
	projection.c.x = 0.0;
	projection.c.y = 0.0;
	projection.c.z = -2 / (far - near);
	projection.c.w = -((far + near) / (far - near));
	projection.d = (t_float4){0.0, 0.0, 0.0, 1.0};
	return (projection);
}

t_float4x4	ft_float4x4_persp(float fov, float aspect, float near, float far)
{
	const float		size = tanf(fov / 2) * near;
	t_float4x4		projection;

	projection.a.x = near / size * aspect;
	projection.a.y = 0.0;
	projection.a.z = 0.0;
	projection.a.w = 0.0;
	projection.b.x = 0.0;
	projection.b.y = near / size;
	projection.b.z = 0.0;
	projection.b.w = 0.0;
	projection.c.x = 0.0;
	projection.c.y = 0.0;
	projection.c.z = -(far + near) / (far - near);
	projection.c.w = (-2 * far * near) / (far - near);
	projection.d = (t_float4){0.0, 0.0, -1.0, 0.0};
	return (projection);
}

t_float4x4	ft_float4x4_view(t_float3 pos, t_float3 x, t_float3 y, t_float3 z)
{
	t_float4x4	axis;
	t_float4x4	offset;

	axis.a = (t_float4){x.x, x.y, x.z, 0.0};
	axis.b = (t_float4){y.x, y.y, y.z, 0.0};
	axis.c = (t_float4){z.x, z.y, z.z, 0.0};
	axis.d = (t_float4){0.0, 0.0, 0.0, 1.0};
	offset.a = (t_float4){1.0, 0.0, 0.0, -pos.x};
	offset.b = (t_float4){0.0, 1.0, 0.0, -pos.y};
	offset.c = (t_float4){0.0, 0.0, 1.0, -pos.z};
	offset.d = (t_float4){0.0, 0.0, 0.0, 1.0};
	return (ft_float4x4_mul(&axis, &offset));
}
