/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:03:13 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/24 13:13:59 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/color.h"

t_argb32	color_to_argb32(t_color c)
{
	return (
		(t_argb32)(255.0f * c.x) << 16 |
		(t_argb32)(255.0f * c.y) << 8 |
		(t_argb32)(255.0f * c.z));
}

t_color		argb32_to_color(t_argb32 c)
{
	return ((t_color){
		(float)(c >> 16 & 0xFF) / 255.0f,
		(float)(c >> 8 & 0xFF) / 255.0f,
		(float)(c & 0xFF) / 255.0f,
	});
}


