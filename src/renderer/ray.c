/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/11 13:58:56 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/ray.h"


#include <stdio.h>

static float	ray_entity_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id entity)
{
	t_geometry const	*geo = ecs_get_component(scene, entity, ECS_GEOMETRY);
	t_float3 const		*pos = ecs_get_component(scene, entity, ECS_POSITION);

	if (geo->type == GEO_SPHERE)
	{
		return (ray_sphere_intersect(self, &geo->data.sphere, pos));
	}
	if (geo->type == GEO_CYLINDER)
	{
		return (ray_cylinder_intersect(self, &geo->data.cylinder, pos));
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

float	ray_cylinder_intersect(
	const t_ray *self,
	const t_cylinder *cyl,
	const t_float3 *pos)
{
	const t_float3	co = ft_float3_sub(self->origin, *pos);
	const float		a = ft_float3_dot(self->direction, self->direction) - powf(ft_float3_dot(self->direction, cyl->normal), 2.0f);
	const float		b = ft_float3_dot(self->direction, co) - (ft_float3_dot(self->direction, cyl->normal) * ft_float3_dot(co, cyl->normal));
	const float		c = ft_float3_dot(co, co) - powf(ft_float3_dot(co, cyl->normal), 2.0f) - (cyl->radius * cyl->radius);
	float 			d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	d = sqrtf(d);
	return ((-b - d) / a);
}

float	ray_sphere_intersect(
	const t_ray *self,
	const t_sphere *sp,
	const t_float3 *pos)
{
	const t_float3	co = ft_float3_sub(self->origin, *pos);
	const float		a = ft_float3_dot(self->direction, self->direction);
	const float		b = ft_float3_dot(co, self->direction);
	const float		c = ft_float3_dot(co, co) - (sp->radius * sp->radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	d = sqrtf(d);
	return ((-b - d) / a);
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

	const t_geometry *geo = ecs_get_component(scene, out->entity, ECS_GEOMETRY);
	if (geo->type == GEO_SPHERE)
	{
		out->normal = *(t_float3 *)ecs_get_component(scene, out->entity, ECS_POSITION);
		out->normal = ft_float3_sub(out->position, out->normal);
		out->normal = ft_float3_normalize(out->normal);
	}
	else if (geo->type == GEO_CYLINDER)
	{
		const t_cylinder *cl = &geo->data.cylinder;
		const t_float3	*pos = ecs_get_component(scene, out->entity, ECS_POSITION);
		float axis_offset = ft_float3_dot(cl->normal, ft_float3_sub(out->position, *pos));

		if (axis_offset > cl->height)
			out->normal = cl->normal;
		else if (axis_offset < 0)
			out->normal = ft_float3_scalar(cl->normal, -1.0f);
		else
			out->normal = ft_float3_normalize(ft_float3_sub(out->position, ft_float3_add(*pos, ft_float3_scalar(cl->normal, axis_offset))));
	}
	return (RT_TRUE);
}
