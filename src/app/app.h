/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:08:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/08 12:06:23 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt.h"
# include "input/input.h"
# include "scene/ecs.h"
# include "renderer/renderer.h"

# include <ft/math.h>
# include <MLX42/MLX42.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

typedef struct s_app
{
	mlx_t		*window;
	mlx_image_t	*framebuffer;
	t_ecs		scene;
	t_input		input;
	t_renderer	renderer;
}	t_app;

t_err	app_init(t_app *app, int argc, char **argv);
void	app_terminate(void *param);

void	app_loop_hook(void *param);

#endif
