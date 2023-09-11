/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/11 16:08:52 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"

#include <stdio.h>

static t_float3	ray_at(const t_ray *self, float d)
{
	return (ft_float3_add(self->origin, ft_float3_scalar(self->direction, d)));
}

static float	ray_entity_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id entity)
{
	t_geometry const	*geo = ecs_get_component(scene, entity, ECS_GEOMETRY);
	t_float3 const		*pos = ecs_get_component(scene, entity, ECS_POSITION);

	if (geo->type == GEO_SPHERE)
	{
		return (ray_sphere_intersect(self, pos, geo->data.sphere.radius));
	}
	if (geo->type == GEO_PLANE)
	{
		return (ray_plane_intersect(self, pos, &geo->data.plane.normal));
	}
	if (geo->type == GEO_CYLINDER)
	{
		return (ray_cylinder_intersect(self, pos, &geo->data.cylinder));
	}
	return (0.0f);
}

float	ray_scene_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id	*opt_entity_hit)
{
	const t_id	*it = scene->renderables.data;
	const t_id	*end = it + scene->renderables.size;
	float		depth;
	float		min_depth;

	min_depth = RAY_MAX;
	while (it != end)
	{
		depth = ray_entity_intersect(self, scene, *it);
		if (depth > RAY_MIN && depth < min_depth)
		{
			if (opt_entity_hit != NULL)
			{
				*opt_entity_hit = *it;
			}
			min_depth = depth;
		}
		++it;
	}
	if (min_depth == RAY_MAX)
	{
		return (0.0f);
	}
	return (min_depth);
}

float	ray_sphere_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const float radius)
{
	const t_float3	oc = ft_float3_sub(self->origin, *pos);
	const float		a = ft_float3_dot(self->direction, self->direction);
	const float		b = ft_float3_dot(oc, self->direction);
	const float		c = ft_float3_dot(oc, oc) - (radius * radius);
	float d;

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
    float    denom;
    float    t;
    denom = ft_float3_dot(*normal, self->direction);
    if (denom < -1e-6)
    {
        t = ft_float3_dot(ft_float3_sub(*pos, self->origin), *normal) / denom;
        return (t);
    }
    return (0.0f);
}

float	ray_disk_intersect(
	const t_ray *self,
	const t_float3 *pos,
	const t_float3 *normal,
	float radius)
{
	const float		depth = ray_plane_intersect(self, pos, normal);
	const t_float3	intersection = ray_at(self, depth);

	if (ft_float3_len(ft_float3_sub(intersection, *pos)) < radius)
		return (0.0f);
	return depth;
}

//static	float ray_cylinder_cap_test(
//	const t_ray *self,
//	float cylinder_intersect,
//	const t_cylinder *cl,
//	const t_float3 *pos)
//{
//	return 0.0f;
//}

float ray_cylinder_intersect(
    const t_ray *self,
    const t_float3 *pos,
    const t_cylinder *cl)
{
	const t_float3	co = ft_float3_sub(self->origin, *pos);
	t_float3		q;
	float 			d;
	float			axis_offset;

	q.x = ft_float3_dot(self->direction, self->direction);
	q.x	-= powf(ft_float3_dot(self->direction, cl->normal), 2.0f);
	q.y = ft_float3_dot(self->direction, cl->normal);
	q.y *= ft_float3_dot(co, cl->normal);
	q.y = ft_float3_dot(self->direction, co) - q.y;
	q.z = ft_float3_dot(co, co);
	q.z -= powf(ft_float3_dot(co, cl->normal), 2.0f);
	q.z -= cl->radius * cl->radius;
	d = (q.y * q.y) - (q.x * q.z);
	if (d < 0)
	{
		return (0.0f);
	}
	d = (-q.y - sqrtf(d)) / q.x;
	axis_offset = ft_float3_dot(ft_float3_sub(ray_at(self, d), *pos),
			ft_float3_scalar(cl->normal, cl->height));
	q = ft_float3_add(*pos, ft_float3_scalar(cl->normal, cl->height));
	if (axis_offset < 0.0f)
		return (ray_disk_intersect(self, &q, &cl->normal, cl->radius));
	return (d);

}

t_float3	calc_surface_normal(t_geometry *geo, t_float3 *pos, t_float3 *hit)
{
	t_float3	normal;

	if (geo->type == GEO_PLANE)
	{
		normal = geo->data.plane.normal;
	}
	if (geo->type == GEO_SPHERE)
	{
		normal = ft_float3_normalize(ft_float3_sub(*hit, *pos));
	}
	if (geo->type == GEO_CYLINDER)
	{
		const t_cylinder	*cl = &geo->data.cylinder;
		float axis_offset = ft_float3_dot(cl->normal, ft_float3_sub(*hit, *pos));

		if (axis_offset > cl->height)
			normal = cl->normal;
		else if (axis_offset < 0)
			normal = ft_float3_scalar(cl->normal, -1.0f);
		else
			normal = ft_float3_normalize(ft_float3_sub(*hit, ft_float3_add(*pos, ft_float3_scalar(cl->normal, axis_offset))));
	}
	return (normal);
}

t_bool	ray_cast(const t_ray *self, const t_ecs *scene, t_hit *out)
{
	const float depth = ray_scene_intersect(self, scene, &out->entity);
	
	if (!depth)
	{
		return (RT_FALSE);
	}
	out->position = ft_float3_scalar(self->direction, depth);
	out->position = ft_float3_add(self->origin, out->position);
	out->normal = calc_surface_normal(
		ecs_get_component(scene, out->entity, ECS_GEOMETRY),
		ecs_get_component(scene, out->entity, ECS_POSITION),
		&out->position);
	return (RT_TRUE);
}
