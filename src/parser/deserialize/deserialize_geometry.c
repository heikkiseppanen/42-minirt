/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_geometry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:29 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/11 14:15:04 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "renderer/color.h"
#include "renderer/geometry.h"

#include <ft/std.h>

t_err	get_color(char *token, t_material *material)
{
	if(!string_to_float3(token, &material->color)
	|| !color_valid(&material->color))
		return (RT_FAILURE);
	material->color = srgb_to_linear(material->color);
	return (RT_SUCCESS);
}

t_err	deserialize_sphere(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	geometry.type = GEO_SPHERE;
	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !ft_is_float(tokens[2])
		|| !get_color(tokens[3], &material))
		return (RT_FAILURE);
	geometry.data.sphere.radius = ft_atof(tokens[2]) / 2;
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	deserialize_plane(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	geometry.type = GEO_PLANE;
	if (array_2d_length(tokens) != 4
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.plane.normal)
		|| !get_color(tokens[3], &material))
		return (RT_FAILURE);
	ft_float3_normalize(geometry.data.plane.normal);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !normal_valid(&geometry.data.plane.normal)
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	deserialize_cylinder(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	geometry.type = GEO_CYLINDER;
	if (array_2d_length(tokens) != 6
		|| !string_to_float3(tokens[1], &point)
		|| !string_to_float3(tokens[2], &geometry.data.cylinder.normal)
		|| !ft_is_float(tokens[3])
		|| !ft_is_float(tokens[4])
		|| !get_color(tokens[5], &material))
		return (RT_FAILURE);
	geometry.data.cylinder.normal = ft_float3_normalize(geometry.data.cylinder.normal);
	geometry.data.cylinder.radius = ft_atof(tokens[3]) / 2;
	geometry.data.cylinder.height = ft_atof(tokens[4]);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !normal_valid(&geometry.data.cylinder.normal)
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
