/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:07:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:30:08 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <ft/math.h>

# define RGBA_BLACK 0x000000FF
# define RGBA_RED 0xFF0000FF
# define RGBA_GREEN 0x00FF00FF
# define RGBA_BLUE 0x0000FFFF

# define GAMMA 2.2f

typedef t_float3		t_color;

typedef unsigned int	t_rgba32;

t_rgba32	color_to_rgba32(t_color c);
t_color		rgba32_to_color(t_rgba32 c);

t_color		srgb_to_linear(t_color c);
t_color		linear_to_srgb(t_color c);

t_color		saturate(t_color c);

#endif
