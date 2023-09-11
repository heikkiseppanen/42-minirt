/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/11 14:14:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "scene/ecs.h"
#include "parser/parser.h"
#include "renderer/color.h"
#include "renderer/light.h"
#include "ray/ray.h"
#include "app/app.h"
#include "camera/camera.h"

#include <ft/cstr.h>
#include <ft/io.h>
#include <stdlib.h>

static void	app_close_hook(void *param)
{
	t_app *const	app = param;

	mlx_close_window(app->window);
}

t_err	app_init(t_app *app, int argc, char **argv)
{
	(void)argc;
	*app = (t_app){};
	if (!ecs_init(&app->scene) || !scene_parser(&app->scene, argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "Error\nScene init failed\n");
		return (RT_FAILURE);
	}
	app->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT", RT_FALSE);
	app->framebuffer = mlx_new_image(app->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!app->window || !app->framebuffer)
	{
		ft_fprintf(STDERR_FILENO, "Error\nMLX: %s\n", mlx_strerror(mlx_errno));
		return (RT_FAILURE);
	}
	mlx_image_to_window(app->window, app->framebuffer, 0, 0);
	mlx_loop_hook(app->window, app_loop_hook, app);
	mlx_close_hook(app->window, app_close_hook, app);
	input_init(&app->input, app->window);
	renderer_init(&app->renderer);
	return (RT_SUCCESS);
}

void	app_terminate(void *param)
{
	t_app *const app = param;

	if (app->framebuffer)
	{
		mlx_delete_image(app->window, app->framebuffer);
	}
	if (app->window)
	{
		mlx_terminate(app->window);
	}
	ecs_del(&app->scene);
}



void	app_loop_hook(void *param)
{
	t_app *const app = param;
	t_ecs *const ecs = &app->scene;
	mlx_image_t *const out = app->framebuffer;

	if (app->input.exit)
	{
		mlx_close_window(app->window);
		return ;
	}
	if (app->input.left_button || app->input.right_button)
	{
		mlx_set_cursor_mode(app->window, MLX_MOUSE_DISABLED);
	}
	else
	{
		mlx_set_cursor_mode(app->window, MLX_MOUSE_NORMAL);
	}
	update_camera(
			app,
			ecs_get_component(ecs, ecs->camera, ECS_CAMERA),
			ecs_get_component(ecs, ecs->camera, ECS_POSITION));
	app->input.mouse_movement = (t_float2){};

	if (app->input.w || app->input.a || app->input.s || app->input.d ||
		app->input.space ||
		app->input.ctrl ||
		app->input.right_button ||
		app->input.left_button)
	{
		renderer_init(&app->renderer);
	}
	renderer_pass(&app->renderer, ecs, out);
}
