/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/14 14:45:11 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "scene/ecs.h"
#include "parser/parser.h"
#include "window/window.h"
#include "renderer/color.h"

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

typedef struct s_ray
{
	t_float3 origin;
	t_float3 direction;
} t_ray;

typedef struct s_ray_hit
{
	t_float3 position;
	t_float3 normal;
} t_ray_hit;

//t_argb32	ray_cast(t_ray *ray, jj

float	ray_sphere_intersect(const t_ray *ray, t_float3 center, float radius)
{
	const t_float3 oc = ft_float3_sub(ray->origin, center);
	const float a = ft_float3_dot(ray->direction, ray->direction);
	const float b = ft_float3_dot(oc, ray->direction);
	const float c = ft_float3_dot(oc, oc) - (radius * radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return -1.0f;
	}
	d = sqrtf(d);
	return ((-b - d) / a);
}

void	camera_update(t_camera *camera, t_float3 position, t_float3 target)
{
	camera->z = ft_float3_sub(position, target);
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

	static t_float3 cam_pos = {0.0f, 1.0f, 1.0f};
	static t_float3 cam_target = {};
	static t_camera camera;

	static t_float3 sphere_pos[] = {
		{0.0f, 0.0f, 0.0f},
		{-0.5f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.5f},
		{0.0f, 0.0f, -0.5f},
	};
	float rad = 0.2f;

	static int init = 1;
	if (init)
	{
		// camera = (t_camera){90.0f, 10.0f, 200.0f, {}, {}, {}};
		init = !init;
	};

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
		cam_target = ft_float3_add(cam_target, total);
	}
	camera_update(&camera, cam_pos, cam_target);
	app->input.mouse_movement = (t_float2){};

	t_float4x4 view = ft_float4x4_view(cam_pos, camera.x, camera.y, camera.z);

	t_float3 sphere_view_coord[4];
	for (int i = 0; i < 4; ++i)
	{
		sphere_view_coord[i] = ft_float3_transform(&view, sphere_pos[i]);
	}
	t_float3 sphere_col[] = {
		(t_color){0.75f, 0.1f, 0.1f},
		(t_color){0.1f, 0.75f, 0.1f},
		(t_color){0.1f, 0.1f, 0.75f},
		ft_float3_scalar((t_color){1.0f, 1.0f, 1.0f}, 1.0f),
	};

	t_float3 light_dir = {1.0f, 0.0f, 0.0};
	light_dir = ft_float3_normalize(light_dir);
	t_float3 light_color = {1.0f, 1.0f, 1.0f};
	float light_intensity = 1.0f;

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
			
			int hit_index = -1;
			float mul = 500.0f;
			for (int i = 0; i < 4; ++i)
			{
				float m = ray_sphere_intersect(&ray, sphere_view_coord[i], rad);
				if (m > 0 && m <= mul)
				{
					hit_index = i;
					mul = m;
				}
			}

			t_argb32 final_color = 0xFF;
			if (hit_index != -1)
			{
				t_float3 normal = ft_float3_scalar(ray.direction, mul);
				normal = ft_float3_add(ray.origin, normal); 
				normal = ft_float3_sub(normal, sphere_view_coord[hit_index]);
				normal = ft_float3_normalize(normal);

				t_color diffuse = sphere_col[hit_index];
				diffuse.x = powf(diffuse.x, 2.2f);
				diffuse.y = powf(diffuse.y, 2.2f);
				diffuse.z = powf(diffuse.z, 2.2f);

				t_color dir_color = light_color;
				dir_color = ft_float3_scalar(dir_color, light_intensity);
				dir_color.x = powf(dir_color.x, 2.2f);
				dir_color.y = powf(dir_color.y, 2.2f);
				dir_color.z = powf(dir_color.z, 2.2f);

				float dir_light_intensity = ft_float3_dot(normal, ft_float3_scalar(light_dir, -1.0f));
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

//				diff_color = ft_float3_scalar(diff_color, 2.2f);

				final_color = color_to_argb32(diff_color);
			}
			
			//hit.x = (hit.x + 1) * 0.5f;
			//hit.y = (hit.y + 1) * 0.5f;
			//hit.z = (hit.z + 1) * 0.5f;
			//col = (int)(hit.x * 255.0f) << 16 | (int)(hit.y * 255.0f) << 8 | (int)(hit.z * 255.0f);

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
