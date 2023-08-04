/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/14 14:45:26 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "scene/ecs.h"
#include "parser/parser.h"
#include "window/window.h"
#include "renderer/color.h"
#include "renderer/ray.h"

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
	mlx_image_t *const out = app->framebuffer;

	static t_ecs	e;
	static t_id		camera_id;
	static t_id		sphere_id;
	static t_id		light_id;

	static int init = 1;
	if (init)
	{
		ecs_init(&e);
		sphere_id = ecs_entity_create(&e);

		t_float3	pos = {0.0f, 0.0f, 0.0f};
		t_geometry geo = {
			.type = GEO_SPHERE,
			.data = {
				.sphere = { 0.2f }
			}
		};
		t_material mat = {
			.color = { 0.75f, 0.15f, 0.15f }
		};

		ecs_add_component(&e, sphere_id, &geo, ECS_GEOMETRY);
		ecs_add_component(&e, sphere_id, &pos, ECS_POSITION);
		ecs_add_component(&e, sphere_id, &mat, ECS_MATERIAL);

		camera_id = ecs_entity_create(&e);

		pos.z = 2.0f;
		t_camera cam = {
			.fov = 90.f,
			.pivot = {},
			.x = {1.0f, 0.0f, 0.0f},
			.y = {0.0f, 1.0f, 0.0f},
			.z = {0.0f, 0.0f, -1.0f}
		};

		ecs_add_component(&e, camera_id, &pos, ECS_POSITION);
		ecs_add_component(&e, camera_id, &cam, ECS_CAMERA);

		light_id = ecs_entity_create(&e);
		t_light light = {
			.attenuation = 1.0f,
			.color = { 0.25, 1.0f, 1.0f }
		};
		pos = (t_float3){ -5.0f, 0.0f, 0.0f };

		ecs_add_component(&e, light_id, &light, ECS_LIGHT);
		ecs_add_component(&e, light_id, &pos, ECS_POSITION);

		init = !init;
	};

	// Update camera

	t_float3 cam_pos = *(t_float3 *)ecs_get_component(&e, camera_id, ECS_POSITION);
	t_camera camera = *(t_camera *)ecs_get_component(&e, camera_id, ECS_CAMERA);

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
	app->input.mouse_movement = (t_float2){};

	// Calculate view matrix

	t_float4x4 view = ft_float4x4_view(cam_pos, camera.x, camera.y, camera.z);

	*(t_float3 *)ecs_get_component(&e, camera_id, ECS_POSITION) = cam_pos;
	*(t_camera *)ecs_get_component(&e, camera_id, ECS_CAMERA) = camera;

	t_float3 sphere_pos = *(t_float3 *)ecs_get_component(&e, sphere_id, ECS_POSITION);
	sphere_pos = ft_float3_transform(&view, sphere_pos);

	t_float3 *light_pos = ecs_get_component(&e, light_id, ECS_POSITION);
	t_light *light = ecs_get_component(&e, light_id, ECS_LIGHT);

	unsigned int y = 0;
	while (y < out->height)
	{
		unsigned int x = 0;
		while (x < out->width)
		{
			t_float3 p;
			p.x = ((float)x + 0.5f) / (float)out->width * 2 - 1;
			p.y = ((float)y + 0.5f) / (float)out->height * 2 - 1;
			p.x *= (float)out->height / (float)out->width;
			p.z = -1.0f;
			p = ft_float3_normalize(p);

			t_ray ray = {{}, p};
			
			t_geometry *geo = ecs_get_component(&e, sphere_id, ECS_GEOMETRY);
			t_material *mat = ecs_get_component(&e, sphere_id, ECS_MATERIAL);
			int hit= 0;
			float mul = 500.0f;
			float m = ray_sphere_intersect(&ray, sphere_pos, geo->data.sphere.radius);
			if (m < mul && m > 0)
			{
				mul = m;
				hit= 1;
			}

			t_argb32 final_color = 0xFF;
			if (hit)
			{
				t_float3 hit = ft_float3_scalar(ray.direction, mul);
				t_float3 normal = hit;
				normal = ft_float3_add(ray.origin, normal); 
				normal = ft_float3_sub(normal, sphere_pos);
				normal = ft_float3_normalize(normal);

				t_color diffuse = mat->color;
				diffuse.x = powf(diffuse.x, 2.2f);
				diffuse.y = powf(diffuse.y, 2.2f);
				diffuse.z = powf(diffuse.z, 2.2f);

				t_color dir_color = light->color;
				dir_color = ft_float3_scalar(dir_color, light->attenuation);
				dir_color.x = powf(dir_color.x, 2.2f);
				dir_color.y = powf(dir_color.y, 2.2f);
				dir_color.z = powf(dir_color.z, 2.2f);

				t_float3 to_light = ft_float3_sub(*light_pos, hit);
				//printf("%f %f %f\n", sphere_pos.x, sphere_pos.y, sphere_pos.z);
				float dir_light_intensity = ft_float3_dot(normal, to_light);
				dir_light_intensity = ft_maxf(0.0f, dir_light_intensity);
				dir_color = ft_float3_scalar(dir_color, dir_light_intensity);

				t_color amb_light = (t_color){0.25f, 0.25f, 0.25f};
				amb_light.x = powf(amb_light.x, 2.2f);
				amb_light.y = powf(amb_light.y, 2.2f);
				amb_light.z = powf(amb_light.z, 2.2f);
				 
				t_color light_total = ft_float3_add(dir_color, amb_light);

				t_float3 diff_color; 
				diff_color.x = ft_clamp(powf(diffuse.x * light_total.x, 1.1 / 2.2f), 0.0f, 1.0f);
				diff_color.y = ft_clamp(powf(diffuse.y * light_total.y, 1.1 / 2.2f), 0.0f, 1.0f);
				diff_color.z = ft_clamp(powf(diffuse.z * light_total.z, 1.1 / 2.2f), 0.0f, 1.0f);

				final_color = color_to_argb32(normal);
			}

			mlx_put_pixel(out, x, out->height - y - 1, final_color);

			++x;
		}
		++y;
	}

	if (app->input.exit)
	{
		mlx_close_window(app->window);
	}
}
