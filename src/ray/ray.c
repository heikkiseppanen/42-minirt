/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/15 11:27:33 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"

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

static t_float3	calculate_surface_normal(
	const t_geometry *geo,
	const t_float3 *pos,
	const t_float3 *hit)
{
	const t_cylinder	*cl;
	float				axis_offset;
	t_float3			normal;

	normal = (t_float3){};
	if (geo->type == GEO_PLANE)
		normal = geo->data.plane.normal;
	else if (geo->type == GEO_SPHERE)
		normal = ft_float3_normalize(ft_float3_sub(*hit, *pos));
	else if (geo->type == GEO_CYLINDER)
	{
		cl = &geo->data.cylinder;
		axis_offset = ft_float3_dot(ft_float3_sub(*hit, *pos), cl->normal);
		if (axis_offset > cl->height - EPSILON)
			normal = cl->normal;
		else if (axis_offset < EPSILON)
			normal = ft_float3_scalar(cl->normal, -1.0f);
		else
			normal = ft_float3_normalize(
					ft_float3_sub(*hit,
						ft_float3_add(*pos,
							ft_float3_scalar(cl->normal, axis_offset))));
	}
	return (normal);
}

t_float3	ray_at(const t_ray *self, float d)
{
	return (ft_float3_add(self->origin, ft_float3_scalar(self->direction, d)));
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
		if (depth > 0.0f && depth < min_depth)
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

t_bool	ray_cast(const t_ray *self, const t_ecs *scene, t_hit *out)
{
	const float	depth = ray_scene_intersect(self, scene, &out->entity);

	if (!depth)
	{
		return (RT_FALSE);
	}
	out->position = ray_at(self, depth);
	out->normal = calculate_surface_normal(
			ecs_get_component(scene, out->entity, ECS_GEOMETRY),
			ecs_get_component(scene, out->entity, ECS_POSITION),
			&out->position);
	return (RT_TRUE);
}
