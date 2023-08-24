/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:06:45 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/24 14:39:27 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/light.h"
#include "renderer/ray.h"
#include "renderer/color.h"

static t_color	calculate_point_light(
	const t_float3 *position,
	const t_float3 *normal,
	const t_light *point,
	const t_float3 *light_position)
{
	t_float3	to_light;
	t_ray		shadow_ray;
	float		light_distance;
	float		scene_distance;
	float		light_intensity;

	to_light = ft_float3_sub(*light_position, *position);
	ft_float3_scalar(point->color, point->attenuation);
	if (!scene_depth || distance_to_light < scene_depth)
	{
		dir_light_intensity = ft_float3_dot(hit.normal, to_light);
		dir_light_intensity = ft_maxf(0.0f, dir_light_intensity);
	}

}

static t_color	calculate_ambient_light(t_light *ambient)
{
	return (ft_float3_scalar(ambient->color, ambient->attenuation));
}

t_color	calculate_surface_light(
	const t_float3 *position,
	const t_float3 *normal,
	const t_ecs *scene)
{
	t_color	total_light;

	total_light = (t_color){};
	if (scene->light)
	{
		total_light = ft_float3_add(total_light, calculate_point_light(
			position, normal,
			ecs_get_component(scene, scene->light, ECS_LIGHT),
			ecs_get_component(scene, scene->light, ECS_POSITION)));
	}
	if (scene->ambient)
	{
		total_light = ft_float3_add(total_light, calculate_ambient_light(
			ecs_get_component(scene, scene->ambient, ECS_LIGHT)));
	}
	return (total_light);
}
