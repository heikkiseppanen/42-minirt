/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/15 11:06:27 by hseppane         ###   ########.fr       */
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
	size_t	i;
	float	distance;

	i = 0;
	while (i < scene->renderables.size)
	{
		t_id	geo_id = *(int *)ft_buf_get(&scene->renderables, i);
		t_geometry *geo = ecs_get_component(scene, geo_id, ECS_GEOMETRY);
		t_float3 *pos = ecs_get_component(scene, geo_id, ECS_GEOMETRY);
		distance = ray_sphere_intersect(r, *pos, geo->data.sphere.radius);
	}
	result->position = ft_float3_add(r->origin, ft_float3_scalar(r->direction, distance));
	return RT_TRUE;
}

float	ray_sphere_intersect(const t_ray *ray, t_float3 center, float radius)
{
	const t_float3 oc = ft_float3_sub(ray->origin, center);
	const float a = ft_float3_dot(ray->direction, ray->direction);
	const float b = ft_float3_dot(oc, ray->direction);
	const float c = ft_float3_dot(oc, oc) - (radius * radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return RT_FALSE;
	}
	d = sqrtf(d);
	return ((-b - d) / a);
	//return (min_positivef((-b - d) / a, (-b + d) / a));
}
