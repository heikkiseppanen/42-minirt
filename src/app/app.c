/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/05 15:58:11 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "scene/ecs.h"
#include "parser/parser.h"
#include "renderer/color.h"
#include "renderer/light.h"
#include "renderer/ray.h"
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

void	draw_quad(t_int2 pos, int size, t_rgba32 color, mlx_image_t *out)
{
	const int	x_min = pos.x;
	const int	x_max = ft_mini(pos.x + size, out->width);
	const int	y_max = ft_mini(pos.y + size, out->height);

	while (pos.y < y_max)
	{
		pos.x = x_min;
		while (pos.x < x_max)
		{
			mlx_put_pixel(out, pos.x, pos.y, color);
			++pos.x;
		}
		++pos.y;
	}
}

#define PREVIEW_CHUNK_SIZE 8

void	app_loop_hook(void *param)
{
	t_app *const app = param;
	t_ecs *const ecs = &app->scene;
	mlx_image_t *const out = app->framebuffer;
	t_camera *camera = ecs_get_component(ecs, ecs->camera, ECS_CAMERA);
	t_float3 *cam_pos = ecs_get_component(ecs, ecs->camera, ECS_POSITION);
	// Update camera
	if (app->input.left_button || app->input.right_button)
	{
		mlx_set_cursor_mode(app->window, MLX_MOUSE_DISABLED);
	}
	else
	{
		mlx_set_cursor_mode(app->window, MLX_MOUSE_NORMAL);
	}

	update_camera(app, camera, cam_pos);

	if (app->input.exit)
	{
		mlx_close_window(app->window);
	}

	app->input.mouse_movement = (t_float2){};

	static int chunk_size = PREVIEW_CHUNK_SIZE;

	if (app->input.w ||
		app->input.a ||
		app->input.s ||
		app->input.d ||
		app->input.space ||
		app->input.ctrl ||
		app->input.right_button ||
		app->input.left_button)
	{
		chunk_size = PREVIEW_CHUNK_SIZE;
	}

	if (!chunk_size)
		return;

	int sample_row = 1;

	t_int2 pixel = {};
	while (pixel.y < (int)out->height)
	{
		if (sample_row && chunk_size > 1 && chunk_size < PREVIEW_CHUNK_SIZE)
			pixel.x = chunk_size;
		else
			pixel.x = 0;
		while (pixel.x < (int)out->width)
		{
			t_rgba32 final_color = RGBA_BLACK;

			// SHADE
			
			t_camera *camera = ecs_get_component(ecs, ecs->camera, ECS_CAMERA);

			t_ray ray = {};
			ray.origin = *(t_float3 *)ecs_get_component(ecs, ecs->camera, ECS_POSITION);

			t_float3 target = camera->pix_00; 
			target = ft_float3_add(target, ft_float3_scalar(camera->u, pixel.x));
			target = ft_float3_add(target, ft_float3_scalar(camera->v, pixel.y));

			ray.direction = ft_float3_sub(target, ray.origin);
			ray.direction = ft_float3_normalize(ray.direction);

			t_hit	hit = {};
			if (ray_cast(&ray, ecs, &hit))
			{
				t_material *mat = ecs_get_component(ecs, hit.entity, ECS_MATERIAL);

				t_color light = calculate_surface_light(&hit.position, &hit.normal, ecs);

				t_color diff_color = ft_float3_mul(mat->color, light); 
				diff_color = saturate(linear_to_srgb(diff_color));

				final_color = color_to_rgba32(diff_color);
			}

			// END OF SHADE
			
			draw_quad(pixel, chunk_size, final_color, out);
			pixel.x += chunk_size;
			if (sample_row && chunk_size > 1 && chunk_size < PREVIEW_CHUNK_SIZE)
				pixel.x += chunk_size;
		}
		sample_row = !sample_row;
		pixel.y += chunk_size;
	}
	chunk_size /= 2;
}
