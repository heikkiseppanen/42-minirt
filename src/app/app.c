/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 11:48:52 by hseppane         ###   ########.fr       */
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

void	render_scanline(t_ecs *scene, int y, t_pass pass, mlx_image_t *out)
{
	t_camera *camera = ecs_get_component(scene, scene->camera, ECS_CAMERA);
	unsigned int x;
	unsigned int chunk_end;

	x = pass.initial_offset;
	while (x < out->width)
	{
		t_ray ray = {};
		ray.origin = *(t_float3 *)ecs_get_component(scene, scene->camera, ECS_POSITION);

		t_float3 pixel = camera->pix_00; 
		pixel = ft_float3_add(pixel, ft_float3_scalar(camera->u, x));
		pixel = ft_float3_add(pixel, ft_float3_scalar(camera->v, y));

		ray.direction = ft_float3_sub(pixel, ray.origin);
		ray.direction = ft_float3_normalize(ray.direction);

		t_rgba32 final_color = RGBA_BLACK;
		t_hit	hit = {};
		if (ray_cast(&ray, scene, &hit))
		{
			t_material *mat = ecs_get_component(scene, hit.entity, ECS_MATERIAL);

			t_color light = calculate_surface_light(&hit.position, &hit.normal, scene);

			t_color diff_color = ft_float3_mul(mat->color, light); 
			diff_color = saturate(linear_to_srgb(diff_color));

			final_color = color_to_rgba32(diff_color);
		}
		chunk_end = x + pass.stride;
		if (chunk_end > out->width)
			chunk_end = out->width;
		while (x < chunk_end)
			mlx_put_pixel(out, x++, y, final_color);
	}
}

void	app_loop_hook(void *param)
{
	t_app *const app = param;
	t_ecs *const ecs = &app->scene;
	mlx_image_t *const out = app->framebuffer;
<<<<<<< HEAD

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
