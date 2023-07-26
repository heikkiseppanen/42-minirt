/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:07:07 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/25 13:42:27 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "minirt.h"

# include <MLX42.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

typedef struct s_window
{
	mtx_t		*context;
	mtx_image_t	*framebuffer;
}	t_window;

t_err	window_init(t_window *w, int width, int height, const char *title);
void	window_del(t_window *win);

#endif
