/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_geometry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:29 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:30 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/std.h>
#include <parser/parser.h>

t_err	deserialize_sphere(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !ft_is_float(tokens[2])
		|| !string_to_float3(tokens[3], &material.color))
		return (parse_error(tokens));
	geometry.data.sphere.radius = 2 / ft_atof(tokens[2]);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL))
		return (parse_error(tokens));
	return (RT_SUCCESS);
}

t_err	deserialize_plane(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.plane.normal)
		|| !string_to_float3(tokens[3], &material.color))
		return (parse_error(tokens));
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY))
		return (parse_error(tokens));
	return (RT_SUCCESS);
}

t_err	deserialize_cylinder(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(tokens) != 6
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.cylinder.normal)
		|| !ft_is_float(tokens[3])
		|| !ft_is_float(tokens[4])
		|| !string_to_float3(tokens[5], &material.color))
		return (parse_error(tokens));
	geometry.data.cylinder.radius = 2 / ft_atof(tokens[3]);
	geometry.data.cylinder.height = ft_atof(tokens[4]);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY))
		return (parse_error(tokens));
	return (RT_SUCCESS);
}
