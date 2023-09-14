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

t_err	deserialize_sphere(t_ecs *ecs, char **tokens)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	geometry.type = GEO_SPHERE;
	if (array_2d_length(tokens) != 4
		|| !get_point(tokens[1], &point)
		|| !get_radius(tokens[2], &geometry.data.sphere.radius)
		|| !get_color(tokens[3], &material.color))
		return (RT_FAILURE);
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
		|| !get_point(tokens[1], &point)
		|| !get_normal(tokens[2], &geometry.data.plane.normal)
		|| !get_color(tokens[3], &material.color))
		return (RT_FAILURE);
	entity = ecs_entity_create(ecs);
	if (!entity
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
		|| !get_point(tokens[1], &point)
		|| !get_normal(tokens[2], &geometry.data.plane.normal)
		|| !get_radius(tokens[3], &geometry.data.cylinder.radius)
		|| !get_height(tokens[4], &geometry.data.cylinder.height)
		|| !get_color(tokens[5], &material.color))
		return (RT_FAILURE);
	entity = ecs_entity_create(ecs);
	if (!entity
		|| !ecs_add_component(ecs, entity, &point, ECS_POSITION)
		|| !ecs_add_component(ecs, entity, &material, ECS_MATERIAL)
		|| !ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY)
		|| !ft_buf_pushback(&ecs->renderables, &entity, 1))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
