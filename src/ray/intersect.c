/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:42:13 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/13 12:48:36 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray/ray.h>

float	ray_sphere_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const float radius)
{
	const t_float3	oc = ft_float3_sub(self->origin, *pos);
	const float		a = ft_float3_dot(self->direction, self->direction);
	const float		b = ft_float3_dot(oc, self->direction);
	const float		c = ft_float3_dot(oc, oc) - (radius * radius);
	float			d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	d = sqrtf(d);
	return ((-b - d) / a);
}

float	ray_plane_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const t_float3 *normal)
{
	float	denom;
	float	depth;

	denom = ft_float3_dot(*normal, self->direction);
	if (denom >= -EPSILON)
	{
		return (0.0f);
	}
	depth = ft_float3_dot(ft_float3_sub(*pos, self->origin), *normal) / denom;
	return (depth);
}

float	ray_disk_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const t_float3 *normal,
	float radius)
{
	const float		depth = ray_plane_intersect(self, pos, normal);
	const t_float3	intersection = ray_at(self, depth);

	if (ft_float3_len(ft_float3_sub(intersection, *pos)) > radius + EPSILON)
		return (0.0f);
	return (depth);
}

static float	ray_tube_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const t_cylinder *cl)
{
	const t_float3	po = ft_float3_sub(self->origin, *pos);
	float			a;
	float			b;
	float			c;
	float			d;

	a = ft_float3_dot(self->direction, self->direction);
	a -= powf(ft_float3_dot(self->direction, cl->normal), 2.0f);
	b = ft_float3_dot(self->direction, cl->normal);
	b *= ft_float3_dot(po, cl->normal);
	b = ft_float3_dot(self->direction, po) - b;
	c = ft_float3_dot(po, po);
	c -= powf(ft_float3_dot(po, cl->normal), 2.0f);
	c -= cl->radius * cl->radius;
	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	return ((-b - sqrtf(d)) / a);
}

float	ray_cylinder_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const t_cylinder *cl)
{
	float		depth;
	float		axis_offset;
	t_float3	to_hit;
	t_float3	cap_pos;
	t_float3	normal;

	depth = ray_tube_intersect(self, pos, cl);
	to_hit = ft_float3_sub(ray_at(self, depth), *pos);
	axis_offset = ft_float3_dot(to_hit, cl->normal);
	if (axis_offset < 0.0f)
	{
		cap_pos = *pos;
		normal = ft_float3_scalar(cl->normal, -1.0f);
		return (ray_disk_intersect(self, &cap_pos, &normal, cl->radius));
	}
	if (axis_offset > cl->height)
	{
		cap_pos = ft_float3_add(*pos, ft_float3_scalar(cl->normal, cl->height));
		normal = cl->normal;
		return (ray_disk_intersect(self, &cap_pos, &normal, cl->radius));
	}
	return (depth);
}
