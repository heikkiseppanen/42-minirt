/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:52:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:21:16 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/ecs.h"

#include "renderer/geometry.h"
#include "renderer/light.h"
#include "camera/camera.h"

#include <ft/math.h>

static size_t	get_component_size(t_ecs_type type)
{
	static size_t	size_table[] = {
		sizeof(t_ecs_list),
		sizeof(t_float3),
		sizeof(t_camera),
		sizeof(t_light),
		sizeof(t_geometry),
		sizeof(t_material),
	};

	return (size_table[type]);
}

t_err	ecs_init(t_ecs *e)
{
	t_ecs_type	type;

	*e = (t_ecs){};
	type = 0;
	if (!ft_buf_init(&e->renderables, 1, sizeof(t_id)))
	{
		return (RT_FAILURE);
	}
	while (type < ECS_TYPE_COUNT)
	{
		if (!ft_buf_init(&e->components[type], 1, get_component_size(type)))
		{
			ecs_del(e);
			return (RT_FAILURE);
		}
		++type;
	}
	return (RT_SUCCESS);
}

void	ecs_del(t_ecs *e)
{
	t_ecs_type	type;

	type = 0;
	ft_buf_del(&e->renderables);
	while (type < ECS_TYPE_COUNT)
	{
		ft_buf_del(e->components + type);
		++type;
	}
}

t_id	ecs_entity_create(t_ecs *e)
{
	t_ecs_list	empty_list;

	empty_list = (t_ecs_list){};
	if (!ft_buf_pushback(&e->components[ECS_LIST], &empty_list, 1))
	{
		return (0);
	}
	return (++e->id_accumulator);
}
