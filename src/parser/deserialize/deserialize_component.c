/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize_component.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:09:18 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/26 10:52:20 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "renderer/color.h"
#include "renderer/geometry.h"

#include <ft/std.h>

t_err	get_color(char *token, t_float3 *color)
{
	if (!string_to_float3(token, color)
		|| !color_valid(color))
		return (RT_FAILURE);
	color->x = color->x / 255.0f;
	color->y = color->y / 255.0f;
	color->z = color->z / 255.0f;
	*color = srgb_to_linear(*color);
	return (RT_SUCCESS);
}

t_err	get_normal(char *token, t_float3 *normal)
{
	if (!string_to_float3(token, normal)
		|| !normal_valid(normal))
		return (RT_FAILURE);
	*normal = ft_float3_normalize(*normal);
	return (RT_SUCCESS);
}

t_err	get_radius(char *token, float *radius)
{
	if (!ft_is_float(token))
		return (RT_FAILURE);
	*radius = ft_atof(token) / 2.0f;
	return (RT_SUCCESS);
}

t_err	get_height(char *token, float *height)
{
	if (!ft_is_float(token))
		return (RT_FAILURE);
	*height = ft_atof(token);
	return (RT_SUCCESS);
}

t_err	get_point(char *token, t_float3 *point)
{
	if (!string_to_float3(token, point))
		return (RT_FAILURE);
	return (RT_SUCCESS);
}
