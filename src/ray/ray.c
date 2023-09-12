/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/12 09:55:13 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"

#include <stdio.h>

t_float3	ray_at(const t_ray *self, float d)
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
    if (denom < -EPSILON)
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

	if (ft_float3_len(ft_float3_sub(intersection, *pos)) > radius)
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


static float	ray_tube_intersect(
    const t_ray *self,
    const t_float3 *pos,
    const t_cylinder *cl)
{
	const t_float3	co = ft_float3_sub(self->origin, *pos);
	float 			a;
	float 			b;
	float 			c;
	float 			d;

	a = ft_float3_dot(self->direction, self->direction);
	a	-= powf(ft_float3_dot(self->direction, cl->normal), 2.0f);
	b = ft_float3_dot(self->direction, cl->normal);
	b *= ft_float3_dot(co, cl->normal);
	b = ft_float3_dot(self->direction, co) - b;
	c = ft_float3_dot(co, co);
	c -= powf(ft_float3_dot(co, cl->normal), 2.0f);
	c -= cl->radius * cl->radius;
	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	return ((-b - sqrtf(d)) / a);
}

float ray_cylinder_intersect(
    const t_ray *self,
    const t_float3 *pos,
    const t_cylinder *cl)
{
	const float	depth = ray_tube_intersect(self, pos, cl);
	float		offset;
	t_float3	cap_pos;
	t_float3	normal;

	offset = ft_float3_dot(ft_float3_sub(ray_at(self, depth), *pos), cl->normal);
	if (offset < 0.0f)
	{
		cap_pos = *pos;
		normal = ft_float3_scalar(cl->normal, -1.0f);
		return (ray_disk_intersect(self, &cap_pos, &normal, cl->radius));
	}
	if (offset > cl->height)
	{
		cap_pos = ft_float3_add(*pos, ft_float3_scalar(cl->normal, cl->height));
		normal = cl->normal;
		return (ray_disk_intersect(self, &cap_pos, &normal, cl->radius));
	}
	return (depth);

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
		float offset = ft_float3_dot(ft_float3_sub(*hit, *pos), cl->normal);

		if (offset > cl->height - EPSILON)
			normal = cl->normal;
		else if (offset < EPSILON)
			normal = ft_float3_scalar(cl->normal, -1.0f);
		else
			normal = ft_float3_normalize(ft_float3_sub(*hit, ft_float3_add(*pos, ft_float3_scalar(cl->normal, offset))));
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
	out->position = ray_at(self, depth);
	out->normal = calc_surface_normal(
		ecs_get_component(scene, out->entity, ECS_GEOMETRY),
		ecs_get_component(scene, out->entity, ECS_POSITION),
		&out->position);
	return (RT_TRUE);
}
