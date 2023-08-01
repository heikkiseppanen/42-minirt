/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:52:41 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/31 15:39:46 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/ecs.h"

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
	t_ecs_type type;

	*e = (t_ecs){};
	type = 0;
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
	while (type < ECS_TYPE_COUNT)
	{
		ft_buf_del(e->components + type);
		++type;
	}
}

t_id	ecs_entity_create(t_ecs *e)
{
	static t_ecs_list	empty_list = {};

	if (!ft_buf_pushback(&e->components[ECS_LIST], &empty_list, 1))
	{
		return (0);
	}
	return (++e->id_accumulator);
}

t_err	ecs_add_component(t_ecs* e, t_id entity, void *data, t_ecs_type type)
{
	t_ecs_list *list;

	list = ft_buf_get(&e->components[ECS_LIST], entity - 1);
	if (list->reference[type] != 0
		|| !ft_buf_pushback(&e->components[type], data, 1))
	{
		return (RT_FAILURE);
	}
	list->reference[type] = e->components[type].size;
	return (RT_SUCCESS);
}

void	*ecs_get_component(const t_ecs* e, t_id entity, t_ecs_type type)
{
	t_ecs_list	*list;
	t_id		id;

	list = ft_buf_get(&e->components[ECS_LIST], entity - 1);
	id = list->reference[type];
	if (!id)
	{
		return (NULL);
	}
	return (ft_buf_get(&e->components[type], id - 1));
}
