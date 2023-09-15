/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:33:56 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 11:40:11 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/ecs.h"

t_err	ecs_add_component(t_ecs *e, t_id entity, void *data, t_ecs_type type)
{
	t_ecs_list	*list;

	list = ft_buf_get(&e->components[ECS_LIST], entity - 1);
	if (list->reference[type] != 0
		|| !ft_buf_pushback(&e->components[type], data, 1))
	{
		return (RT_FAILURE);
	}
	list->reference[type] = e->components[type].size;
	return (RT_SUCCESS);
}

void	*ecs_get_component(const t_ecs *e, t_id entity, t_ecs_type type)
{
	t_ecs_list	*list;
	t_id		id;

	list = ft_buf_get(&e->components[ECS_LIST], entity - 1);
	id = list->reference[type];
	return (ft_buf_get(&e->components[type], id - 1));
}
