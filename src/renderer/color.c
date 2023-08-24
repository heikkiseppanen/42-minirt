/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:03:13 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/24 12:27:23 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/color.h"

t_argb32	color_to_argb32(t_color c)
{
	return (
		(t_argb32)(255.0f * c.x) << 24 |
		(t_argb32)(255.0f * c.y) << 16 |
		(t_argb32)(255.0f * c.z) << 8  | 0xFF);
}

t_color		argb32_to_color(t_argb32 c)
{
	return ((t_color){
		(float)(c >> 24 & 0xFF) / 255.0f,
		(float)(c >> 16 & 0xFF) / 255.0f,
		(float)(c >> 8 & 0xFF) / 255.0f, 
	});
}

t_color		srgb_to_linear(t_color c)
{
	return (t_color){
		powf(c.x, GAMMA),
		powf(c.y, GAMMA),
		powf(c.z, GAMMA),
	};
}

t_color		linear_to_srgb(t_color c)
{
	return (t_color){
		powf(c.x, 1.0f / GAMMA),
		powf(c.y, 1.0f / GAMMA),
		powf(c.z, 1.0f / GAMMA),
	};
}

t_color		saturate(t_color c)
{
	return (t_color){
		ft_clamp(c.x, 0.0f, 1.0f),
		ft_clamp(c.y, 0.0f, 1.0f),
		ft_clamp(c.z, 0.0f, 1.0f),
	};
}



