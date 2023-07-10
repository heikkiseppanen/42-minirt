/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:08:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/25 14:19:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt.h"
# include "input/input.h"
# include <ft/math.h>



typedef struct s_plane
{
	t_float3	point;
	t_float3	normal;
}	t_plane;


# include <MLX42/MLX42.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

typedef struct s_app
{
	mlx_t		*window;
	mlx_image_t	*framebuffer;
	t_input		input;
}	t_app;

t_err	app_init(t_app *app, int argc, char **argv);

void	app_close_hook(void *param);
void	app_loop_hook(void *param);

#endif
