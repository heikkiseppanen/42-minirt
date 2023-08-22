/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/25 14:55:47 by hseppane         ###   ########.fr       */
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

void	app_close_hook(void *param)
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

void	camera_update(t_camera *camera, t_float3 position)
{
	camera->z = ft_float3_sub(position, camera->pivot);
	camera->z = ft_float3_normalize(camera->z);
	camera->y = (t_float3){0.0, 1.0, 0.0};
	camera->x = ft_float3_cross(camera->y, camera->z);
	camera->x = ft_float3_normalize(camera->x);
	camera->y = ft_float3_cross(camera->z, camera->x);
}

void	app_loop_hook(void *param)
{
	t_app *const app = param;
	t_ecs *const ecs = &app->scene;
	mlx_image_t *const out = app->framebuffer;

	// Update camera
	update_camera_pos(app, ecs_get_component(ecs, ecs->camera, ECS_POSITION));

	t_float3 cam_pos = *(t_float3 *)ecs_get_component(ecs, ecs->camera, ECS_POSITION);
	t_camera camera = *(t_camera *)ecs_get_component(ecs, ecs->camera, ECS_CAMERA);

	if (app->input.left_button)
	{
		cam_pos = ft_float3_rot_y(cam_pos, app->input.mouse_movement.x * app->window->delta_time);
		cam_pos = ft_float3_rot_axis(cam_pos, camera.x, app->input.mouse_movement.y * app->window->delta_time);
	}
	if (app->input.right_button)
	{
		t_float3 offset_x = ft_float3_scalar(camera.x, app->input.mouse_movement.x);
		t_float3 offset_y = ft_float3_scalar(camera.y, -app->input.mouse_movement.y);
		t_float3 total = ft_float3_add(offset_x, offset_y);

		total = ft_float3_scalar(total, app->window->delta_time);
		cam_pos = ft_float3_add(cam_pos, total);
		camera.pivot = ft_float3_add(camera.pivot, total);
	}
	camera_update(&camera, cam_pos);

	// Canvas?

	static t_float3 pix_00; // SHOULD BE ADDED TO CAMERA
	static t_float3 u;      // SHOULD BE ADDED TO CAMERA
	static t_float3 v;      // SHOULD BE ADDED TO CAMERA

	float aspect_ratio = (float)out->height / (float)out->width;
	float dx = tanf(ft_rad(camera.fov / 2));
	float dy = dx * aspect_ratio;

	u = ft_float3_scalar(camera.x, 2 * dx / out->width);
	v = ft_float3_scalar(camera.y, -2 * dy / out->height);

	pix_00 = ft_float3_sub(cam_pos, camera.z);
	pix_00 = ft_float3_add(pix_00, ft_float3_scalar(camera.x, -dx));
	pix_00 = ft_float3_add(pix_00, ft_float3_scalar(camera.y, dy));
	pix_00 = ft_float3_add(pix_00, ft_float3_scalar(u, 0.5f));
	pix_00 = ft_float3_add(pix_00, ft_float3_scalar(v, 0.5f));

	app->input.mouse_movement = (t_float2){};

	*(t_float3 *)ecs_get_component(ecs, ecs->camera, ECS_POSITION) = cam_pos;
	*(t_camera *)ecs_get_component(ecs, ecs->camera, ECS_CAMERA) = camera;

	unsigned int y = 0;
	while (y < out->height)
	{
		unsigned int x = 0;
		while (x < out->width)
		{
			t_ray ray = {};
			ray.origin = *(t_float3 *)ecs_get_component(ecs, ecs->camera, ECS_POSITION);

			t_float3 pixel = pix_00; 
			pixel = ft_float3_add(pixel, ft_float3_scalar(u, x));
			pixel = ft_float3_add(pixel, ft_float3_scalar(v, y));

			ray.direction = ft_float3_sub(pixel, ray.origin);
			ray.direction = ft_float3_normalize(ray.direction);

			t_argb32 final_color = 0xFF;
			t_hit	hit = {};
			if (ray_cast(&ray, ecs, &hit))
			{
				t_material *mat = ecs_get_component(ecs, hit.entity, ECS_MATERIAL);

				t_color light = calculate_surface_light(&hit.position, &hit.normal, ecs);

				t_float3 diff_color; 
				diff_color.x = mat->color.x * light.x;
				diff_color.y = mat->color.y * light.y;
				diff_color.z = mat->color.z * light.z;
				diff_color = saturate(linear_to_srgb(diff_color));

				final_color = color_to_argb32(diff_color);
			}

			mlx_put_pixel(out, x, y, final_color);

			++x;
		}
		++y;
	}

	if (app->input.exit)
	{
		mlx_close_window(app->window);
	}
}
