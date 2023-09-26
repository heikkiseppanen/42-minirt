/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_camera_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:35 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/26 10:50:04 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "renderer/color.h"
#include "renderer/light.h"
#include "camera/camera.h"

#include <ft/cstr.h>
#include <ft/std.h>

t_err	deserialize_ambient(t_ecs *ecs, char **tokens)
{
	t_light	ambient;

	if (ecs->ambient)
		return (RT_FAILURE);
	if (array_2d_length(tokens) != 3
		|| !ft_is_float(tokens[1])
		|| !get_color(tokens[2], &ambient.color))
		return (RT_FAILURE);
	ambient.attenuation = ft_atof(tokens[1]);
	ecs->ambient = ecs_entity_create(ecs);
	if (!ecs->ambient
		|| (ambient.attenuation < 0.0f || ambient.attenuation > 1.0f)
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
		|| !get_color(tokens[3], &light.color))
		return (RT_FAILURE);
	light.attenuation = ft_atof(tokens[2]);
	ecs->light = ecs_entity_create(ecs);
	if (!ecs->light
		|| (light.attenuation < 0.0f || light.attenuation > 1.0f)
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
	camera.speed = 3.0f;
	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !get_normal(tokens[2], &camera.pivot)
		|| !ft_is_float(tokens[3]))
		return (RT_FAILURE);
	camera.fov = ft_atof(tokens[3]);
	if (camera.fov == 180.0f)
		camera.fov -= 1e-5f;
	camera.fov = ft_rad(camera.fov);
	ecs->camera = ecs_entity_create(ecs);
	if (!ecs->camera
		|| (camera.fov < 0.0f || camera.fov > 180.0f)
		|| !ecs_add_component(ecs, ecs->camera, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, ecs->camera, &camera, ECS_CAMERA))
		return (RT_FAILURE);
	reorient_camera(&camera);
	return (RT_SUCCESS);
}
