/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:06:45 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/15 11:15:44 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/light.h"
#include "renderer/color.h"
#include "ray/ray.h"

static t_color	calculate_point_light(
	const t_float3 *position,
	const t_float3 *normal,
	const t_ecs *scene)
{
	const t_light	*source = ecs_get_component(scene, scene->light, ECS_LIGHT);
	t_ray			light;
	float			light_distance;
	float			scene_distance;
	float			light_intensity;

	light.origin = ft_float3_add(*position,
			ft_float3_scalar(*normal, 10 * EPSILON));
	light.direction = ft_float3_sub(
			*(t_float3 *)ecs_get_component(scene, scene->light, ECS_POSITION),
			*position);
	light_distance = ft_float3_len(light.direction);
	light.direction = ft_float3_normalize(light.direction);
	scene_distance = ray_scene_intersect(&light, scene, NULL);
	if (!scene_distance || scene_distance > light_distance + EPSILON)
	{
		light_intensity = ft_float3_dot(*normal, light.direction);
		light_intensity = ft_maxf(0.0f, light_intensity);
		light_intensity *= source->attenuation;
		return (ft_float3_scalar(source->color, light_intensity));
	}
	return ((t_color){});
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
		total_light = ft_float3_add(total_light,
				calculate_point_light(position, normal, scene));
	}
	if (scene->ambient)
	{
		total_light = ft_float3_add(total_light,
				calculate_ambient_light(
					ecs_get_component(scene, scene->ambient, ECS_LIGHT)));
	}
	return (total_light);
}
