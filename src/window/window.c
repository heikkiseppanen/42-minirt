/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:09:22 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 19:09:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window/window.h"
#include "input/input.h"

#include <stdlib.h>
#include <mlx.h>

static int	frame_init(t_frame *empty, const t_window *context)
{
	int	bits;
	int	width;
	int	endian;

	*empty = (t_frame){};
	empty->width = context->width;
	empty->height = context->height;
	empty->data = mlx_get_data_addr(context->mlx_image, &bits, &width, &endian);
	if (!empty->data)
		return (0);
	empty->depth_buffer = malloc(empty->width * empty->height * sizeof(float));
	if (!empty->depth_buffer)
		return (0);
	empty->color_bytes = bits / 8;
	empty->endian = endian;
	return (1);
}

int	window_init(t_window *empty, int width, int height, char *title)
{
	empty->mlx_handle = mlx_init();
	if (!empty->mlx_handle)
		return (0);
	empty->mlx_window = mlx_new_window(empty->mlx_handle, width, height, title);
	if (!empty->mlx_window)
		return (0);
	empty->mlx_image = mlx_new_image(empty->mlx_handle, width, height);
	if (!empty->mlx_image)
		return (0);
	empty->width = width;
	empty->height = height;
	if (!frame_init(&empty->framebuffer, empty))
		return (0);
	return (1);
}

void	frame_clear(t_frame *buf, unsigned int color)
{
	unsigned int	*color_it;
	unsigned int	*color_end;
	float			*depth_it;
	float			*depth_end;

	color_it = (unsigned int *)buf->data;
	color_end = color_it + buf->width * buf->height;
	depth_it = buf->depth_buffer;
	depth_end = depth_it + buf->width * buf->height;
	while (color_it != color_end)
		*color_it++ = color;
	while (depth_it != depth_end)
		*depth_it++ = 1.0;
}

void	window_swap_buf(t_window *win)
{
	mlx_put_image_to_window(
		win->mlx_handle,
		win->mlx_window,
		win->mlx_image, 0, 0);
}

void	window_del(t_window *win)
{
	mlx_destroy_image(win->mlx_handle, win->mlx_image);
	mlx_destroy_window(win->mlx_handle, win->mlx_window);
	free(win->framebuffer.depth_buffer);
	*win = (t_window){};
}
