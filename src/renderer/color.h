/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:07:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/26 12:52:47 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <ft/math.h>

# define ARGB_RED 0xFF0000FF
# define ARGB_GREEN 0x00FF00FF
# define ARGB_BLUE 0x0000FFFF

typedef t_float3 t_color;

typedef unsigned int t_argb32;

t_argb32	color_to_argb32(t_color c);
t_color		argb32_to_color(t_argb32 c);

#endif
