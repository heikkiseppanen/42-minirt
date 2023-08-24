/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_camera_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:35 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/24 12:45:56 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "renderer/color.h"

#include <ft/cstr.h>
#include <ft/std.h>

t_err	deserialize_ambient(t_ecs *ecs, char **tokens)
{
	t_light	ambient;

	if (ecs->ambient)
		return (RT_FAILURE);
	if (array_2d_length(tokens) != 3
		|| !ft_is_float(tokens[1])
		|| !string_to_float3(tokens[2], &ambient.color)
		|| !color_valid(&ambient.color))
		return (RT_FAILURE);
	ambient.color = srgb_to_linear(ambient.color);
	ambient.attenuation = ft_atof(tokens[1]);
	ecs->ambient = ecs_entity_create(ecs);
	if (!ecs->ambient
		|| (ambient.attenuation < 0.0 || ambient.attenuation > 1.0)
		|| !ecs_add_component(ecs, ecs->ambient, &ambient, ECS_LIGHT))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	deserialize_light(t_ecs *ecs, char **tokens)
{
	t_float3	point;
	t_light		light;

	if (ecs->light)
		return (RT_FAILURE);
	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !ft_is_float(tokens[2])
		|| !string_to_float3(tokens[3], &light.color)
		|| !color_valid(&light.color))
		return (RT_FAILURE);
	light.color = srgb_to_linear(light.color);
	light.attenuation = ft_atof(tokens[2]);
	ecs->light = ecs_entity_create(ecs);
	if (!ecs->light
		|| (light.attenuation < 0.0 || light.attenuation > 1.0)
		|| !ecs_add_component(ecs, ecs->light, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, ecs->light, &light, ECS_LIGHT))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	deserialize_camera(t_ecs *ecs, char **tokens)
{
	t_float3	point;
	t_camera	camera;

	if (ecs->camera)
		return (RT_FAILURE);
	ft_memset(&camera, 0, sizeof(camera));
	camera.x.x = 1;
	camera.y.y = 1;
	camera.z.z = 1;
	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &camera.pivot)
		|| !ft_is_float(tokens[3]))
		return (RT_FAILURE);
	camera.pivot = ft_float3_add(point, ft_float3_normalize(camera.pivot));
	camera.fov = ft_atof(tokens[3]);
	ecs->camera = ecs_entity_create(ecs);
	if (!ecs->camera
		|| (camera.fov < 0.0 || camera.fov > 180.0)
		|| !ecs_add_component(ecs, ecs->camera, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, ecs->camera, &camera, ECS_CAMERA))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
