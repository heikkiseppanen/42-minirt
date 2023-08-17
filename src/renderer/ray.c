/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/17 12:21:05 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/ray.h"

//static float	min_positivef(float a, float b)
//{
//	(void)a;
//	(void)b;
//	return 0;
//}

t_bool	ray_cast(const t_ray *r, const t_ecs *scene, t_hit *result)
{
	const t_id *it = scene->renderables.data;
	const t_id *end = it + scene->renderables.size;
	t_id	entity;
	float	distance;
	float	min_distance;

	entity = 0;
	min_distance = RAY_MAX;
	while (it != end)
	{
		t_geometry *geo = ecs_get_component(scene, *it, ECS_GEOMETRY);
		t_float3 *pos = ecs_get_component(scene, *it, ECS_GEOMETRY);
		distance = ray_sphere_intersect(r, &geo->data.sphere, pos);
		if (distance < min_distance)
		{
			entity = *it;
			min_distance = distance;
		}
		++it;
	}
	if (min_distance == RAY_MAX)
		return (RT_FALSE);
	result->position = ft_float3_add(r->origin, ft_float3_scalar(r->direction, min_distance));
	///result->normal = ft_float3_
	return (RT_TRUE);
}

//static float	quadratic_solver(float a, float half_b, float c)
//{
//	const float d = (half_b * half_b) - (a * c);
//}

float	ray_sphere_intersection(
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
