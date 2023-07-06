/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:07:07 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 19:07:09 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

typedef struct s_frame
{
	char	*data;
	float	*depth_buffer;
	int		color_bytes;
	int		width;
	int		height;
	int		endian;
}	t_frame;

typedef struct s_window
{
	void		*mlx_handle;
	void		*mlx_window;
	void		*mlx_image;
	int			width;
	int			height;
	t_frame		framebuffer;
}	t_window;

enum e_window_event_type
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17
};

int		window_init(t_window *win, int width, int height, char *title);
void	window_del(t_window *win);

void	window_swap_buf(t_window *win);

void	frame_clear(t_frame *buf, unsigned int color);

#endif
