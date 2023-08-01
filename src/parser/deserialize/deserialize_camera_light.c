/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_camera_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:35 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:37 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/cstr.h>
#include <ft/std.h>
#include <parser/parser.h>

t_err	deserialize_ambient(t_ecs *ecs, char **tokens)
{
	t_id	entity;
	t_light	ambient;

	if (array_2d_length(tokens) != 3)
		return (parse_error(tokens));
	if (!ft_is_float(tokens[1]))
		return (parse_error(tokens));
	ambient.attenuation = ft_atof(tokens[1]);
	if (!string_to_float3(tokens[2], &ambient.color))
		return (parse_error(tokens));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(tokens));
	ecs_add_component(ecs, entity, &ambient, ECS_LIGHT);
	return (RT_SUCCESS);
}

t_err	deserialize_light(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_light		light;

	if (array_2d_length(tokens) != 4)
		return (parse_error(tokens));
	if (!string_to_float3(tokens[1], &point))
		return (parse_error(tokens));
	if (!ft_is_float(tokens[2]))
		return (parse_error(tokens));
	light.attenuation = ft_atof(tokens[2]);
	if (!string_to_float3(tokens[3], &light.color))
		return (parse_error(tokens));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(tokens));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &light, ECS_LIGHT);
	return (RT_SUCCESS);
}

t_err	deserialize_camera(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_camera	camera;

	ft_memset(&camera, 0, sizeof(camera));
	camera.x.x = 1;
	camera.y.y = 1;
	camera.z.z = 1;
	if (array_2d_length(tokens) != 4)
		return (parse_error(tokens));
	if (!string_to_float3(tokens[1], &point))
		return (parse_error(tokens));
	if (!string_to_float3(tokens[2], &camera.pivot))
		return (parse_error(tokens));
	if (!ft_is_float(tokens[3]))
		return (parse_error(tokens));
	camera.fov = ft_atof(tokens[3]);
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(tokens));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &camera, ECS_CAMERA);
	return (RT_SUCCESS);
}
