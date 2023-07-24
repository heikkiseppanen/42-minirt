/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:51:25 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/24 11:21:34 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECS_H
# define ECS_H

# include "minirt.h"

# include <ft/buf.h>
# include <ft/math.h>

typedef unsigned int t_id;

typedef enum e_ecs_type
{
	ECS_LIST = 0,
	ECS_TRANSFORM,
	ECS_CAMERA,
	ECS_LIGHT,
	ECS_GEOMETRY,
	ECS_MATERIAL,
	ECS_TYPE_COUNT
}	t_ecs_type;

// PLACEHOLDER COMPONENTS

typedef struct s_ecs_list
{
	t_id	reference[ECS_TYPE_COUNT];
}	t_ecs_list;

typedef struct s_transform
{
	t_float3	position;
}	t_transform;

typedef struct s_camera
{
	float		fov;
	float		near;
	float		far;
	t_float3	x;
	t_float3	y;
	t_float3	z;
}	t_camera;

typedef struct s_light
{
}	t_light;

typedef struct s_sphere
{
	float	diameter;
}	t_sphere;

typedef struct s_geometry
{
	t_sphere	sphere;
}	t_geometry;

typedef struct s_material
{
	t_float3	color;
}	t_material;

typedef struct s_ecs
{
	t_id	id_accumulator;
	t_buf	components[ECS_TYPE_COUNT];
}	t_ecs;

t_err	ecs_init(t_ecs *e);
void	ecs_del(t_ecs *e);

// Creates a new empty entity. Returns 0 on failure.
t_id	ecs_entity_create(t_ecs* e);

// Adds a new component for the provided entity.
t_err	ecs_add_component(t_ecs* e, t_id entity, void *data, t_ecs_type type);

// Returns a reference to a component of an entity or NULL if none.
void	*ecs_get_component(const t_ecs* e, t_id entity, t_ecs_type type);

#endif
