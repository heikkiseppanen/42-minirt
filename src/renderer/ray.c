/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/21 09:48:07 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/ray.h"

static float	ray_entity_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id entity)
{
	t_geometry const	*geo = ecs_get_component(scene, entity, ECS_GEOMETRY);
	t_float3 const		*pos = ecs_get_component(scene, entity, ECS_POSITION);

	return (ray_sphere_intersect(self, &geo->data.sphere, pos));
}

float	ray_sphere_intersect(
	const t_ray *ray,
	const t_sphere *sp,
	const t_float3 *pos)
{
	const t_float3	oc = ft_float3_sub(ray->origin, *pos);
	const float		a = ft_float3_dot(ray->direction, ray->direction);
	const float		b = ft_float3_dot(oc, ray->direction);
	const float		c = ft_float3_dot(oc, oc) - (sp->radius * sp->radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (-1.0f);
	}
	d = sqrtf(d);
	return ((-b - d) / a);
}

t_bool	ray_cast(const t_ray *self, const t_ecs *scene, t_hit *out)
{
	const t_id	*it = scene->renderables.data;
	const t_id	*end = it + scene->renderables.size;
	float		depth;
	float		min_depth;

	min_depth = RAY_MAX;
	while (it != end)
	{
		depth = ray_entity_intersect(self, scene, *it);
		if (depth > 0 && depth < min_depth)
		{
			out->entity = *it;
			min_depth = depth;
		}
		++it;
	}
	if (min_depth == RAY_MAX)
		return (RT_FALSE);
	out->position = ft_float3_scalar(self->direction, min_depth);
	out->position = ft_float3_add(self->origin, out->position);
	out->normal = *(t_float3 *)ecs_get_component(scene, out->entity, ECS_POSITION);
	out->normal = ft_float3_sub(out->position, out->normal);
	out->normal = ft_float3_normalize(out->normal);
	return (RT_TRUE);
}

//static float	quadratic_solver(float a, float half_b, float c)
//{
//	const float d = (half_b * half_b) - (a * c);
//}

