/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:09:22 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/25 13:41:12 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window/window.h"

#include "minirt.h"
#include "input/input.h"

#include <stdlib.h>

t_err	window_init(t_window *w, int width, int height, const char *title)
{
	*w = (t_window){};
	w->context = mlx_init(width, height, title, RT_FALSE);
	if (!w->context)
	{
		return (RT_FAILURE);
	}
	w->framebuffer = mlx_;
	if (!w->window)
		return (0);
	w->width = width;
	w->height = height;
	if (!framebuf_init(&w->framebuffer, w))
		return (0);
	return (1);
}

void	framebuf_clear(t_framebuf *buf, unsigned int color)
{
	unsigned int	*color_buffer;
	unsigned int	size;
	unsigned int	i;

	color_buffer = (unsigned int *)buf->color;
	size = buf->width * buf->height;
	i = 0;
	while (i < size)
	{
		color_buffer[i] = color;
		buf->depth[i] = 1.0;
		++i;
	}
}

void	window_del(t_window *win)
{
	mlx_destroy_image(win->handle, win->image);
	mlx_destroy_window(win->handle, win->window);
	free(win->framebuffer.depth);
	*win = (t_window){};
}
