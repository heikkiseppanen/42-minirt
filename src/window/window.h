/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:07:07 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/07 09:49:18 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

typedef struct s_framebuf
{
	char	*color;
	float	*depth;
	int		color_bytes;
	int		width;
	int		height;
	int		endian;
}	t_framebuf;

typedef struct s_window
{
	void		*handle;
	void		*window;
	void		*image;
	int			width;
	int			height;
	t_framebuf	framebuffer;
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

void	framebuf_clear(t_framebuf *buf, unsigned int color);

#endif
