/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:48:33 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "scene/ecs.h"
#include "parser/parser.h"
#include "camera/camera.h"

#include <ft/io.h>

static void	app_close_hook(void *param)
{
	t_app *const	app = param;

	mlx_close_window(app->window);
}

t_err	app_init(t_app *app, int argc, char **argv)
{
	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Error\nInvalid arguments.\n");
		return (RT_FAILURE);
	}
	*app = (t_app){};
	if (!ecs_init(&app->scene) || !scene_parser(&app->scene, argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "Error\nScene init failed.\n");
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
	t_app *const	app = param;

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
	t_app *const		app = param;

	if (app->input.escape)
	{
		mlx_close_window(app->window);
		return ;
	}
	update_camera(
		app,
		ecs_get_component(&app->scene, app->scene.camera, ECS_CAMERA),
		ecs_get_component(&app->scene, app->scene.camera, ECS_POSITION));
	renderer_pass(&app->renderer, &app->scene, app->framebuffer);
	app->input.mouse_movement = (t_float2){};
}
