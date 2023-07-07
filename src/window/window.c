/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:09:22 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/07 10:39:58 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window/window.h"
#include "input/input.h"

#include <stdlib.h>
#include <mlx.h>

static int	framebuf_init(t_framebuf *empty, const t_window *context)
{
	int	bits;
	int	width;
	int	endian;

	*empty = (t_framebuf){};
	empty->width = context->width;
	empty->height = context->height;
	empty->color = mlx_get_data_addr(context->image, &bits, &width, &endian);
	if (!empty->color)
		return (0);
	empty->depth = malloc(empty->width * empty->height * sizeof(*empty->depth));
	if (!empty->depth)
		return (0);
	empty->color_bytes = bits / 8;
	empty->endian = endian;
	return (1);
}

int	window_init(t_window *empty, int width, int height, char *title)
{
	empty->handle = mlx_init();
	if (!empty->handle)
		return (0);
	empty->window = mlx_new_window(empty->handle, width, height, title);
	if (!empty->window)
		return (0);
	empty->image = mlx_new_image(empty->handle, width, height);
	if (!empty->image)
		return (0);
	empty->width = width;
	empty->height = height;
	if (!framebuf_init(&empty->framebuffer, empty))
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

void	window_swap_buf(t_window *win)
{
	mlx_put_image_to_window(
		win->handle,
		win->window,
		win->image, 0, 0);
}

void	window_del(t_window *win)
{
	mlx_destroy_image(win->handle, win->image);
	mlx_destroy_window(win->handle, win->window);
	free(win->framebuffer.depth);
	*win = (t_window){};
}
