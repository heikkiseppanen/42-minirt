/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:51:25 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:22:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECS_H
# define ECS_H

# include "minirt.h"

# include <ft/buf.h>
# include <ft/math.h>

typedef unsigned int	t_id;

typedef enum e_ecs_type
{
	ECS_LIST = 0,
	ECS_POSITION,
	ECS_CAMERA,
	ECS_LIGHT,
	ECS_GEOMETRY,
	ECS_MATERIAL,
	ECS_TYPE_COUNT
}	t_ecs_type;

typedef struct s_ecs_list
{
	t_id	reference[ECS_TYPE_COUNT];
}	t_ecs_list;

typedef struct s_ecs
{
	t_buf	components[ECS_TYPE_COUNT];
	t_id	id_accumulator;
	t_id	light;
	t_id	camera;
	t_id	ambient;
	t_buf	renderables;
}	t_ecs;

t_err	ecs_init(t_ecs *e);
void	ecs_del(t_ecs *e);

// Creates a new empty entity. Returns 0 on failure.
t_id	ecs_entity_create(t_ecs *e);

// Adds a new component for the provided entity.
t_err	ecs_add_component(t_ecs *e, t_id entity, void *data, t_ecs_type type);

// Returns a reference to a component of an entity or NULL if none.
void	*ecs_get_component(const t_ecs *e, t_id entity, t_ecs_type type);

#endif
