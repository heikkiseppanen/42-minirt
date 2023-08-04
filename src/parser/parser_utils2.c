/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:17 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:20 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/cstr.h>
#include <ft/std.h>
#include <stdio.h>
#include <parser/parser.h>

t_bool	color_valid(t_float3 *color)
{
	if ((color->x < 0.0 || color->x > 255.0)
		|| (color->y < 0.0 || color->y > 255)
		|| (color->z < 0.0 || color->z > 255.0))
		return (RT_FALSE);
	return (RT_SUCCESS);
}

t_bool	normal_valid(t_float3 *normal)
{
	if (!normal->x && !normal->y && !normal->z)
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
