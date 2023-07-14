/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/14 08:54:04 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "window/window.h"

#include <ft/io.h>
#include <mlx.h>
#include <stdlib.h>

int	app_init(t_app *empty, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (!window_init(&empty->window, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT"))
	{
		return (0);
	}
	mlx_loop_hook(empty->window.handle, app_loop, empty);
	mlx_hook(empty->window.window, ON_DESTROY, 0, app_terminate, empty);
	input_init(&empty->input, empty->window.window);
	return (1);
}

int	app_terminate(t_app *instance, int exit_code)
{
	window_del(&instance->window);
	exit(exit_code);
	return (1);
}

#define ARGB_RED 0x00FF0000
#define ARGB_GREEN 0x0000FF00
#define ARGB_BLUE 0x000000FF
#define ARGB_NORD_RED 0x00BF616A
#define ARGB_NORD_GREEN 0x00A3BE8C
#define ARGB_NORD_BLUE 0x002E3440

typedef unsigned int t_argb32;

typedef char t_bool;

#define TRUE 1
#define FALSE 0

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

void framebuf_put_pixel(t_framebuf *output, t_float3 position, t_argb32 color)
{
	size_t offset;

	position.y = output->height - position.y - 1;
	offset = ((int)position.x + (int)position.y * output->width);
	offset *= sizeof(color);
	*((unsigned int *)(output->color + offset)) = color;
}

typedef struct s_camera
{
	float		fov;
	float		aspect;
	float		near;
	float		far;
	t_float3	x;
	t_float3	y;
	t_float3	z;
}	t_camera;

t_camera	camera_create(float fov, float aspect_ratio, float near, float far)
{
	return (t_camera){fov, aspect_ratio, near, far, {}, {}, {}};
	
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

int	app_loop(t_app *app)
{
	t_window *const	window = &app->window;
	t_framebuf *out = &window->framebuffer;
	const float aspect = (float)out->width / (float)out->height;

	static t_float3 cam_pos = {0.0f, 1.0f, 0.1f};
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
		camera = camera_create(90.0f, aspect, 0.1f, 100.0f);
		init = 0;
	}

	if (app->input.left_button)
	{
		cam_pos = ft_float3_rot_y(cam_pos, app->input.mouse_movement.x * 0.01f);
		cam_pos = ft_float3_rot_axis(cam_pos, camera.x, app->input.mouse_movement.y * 0.01f);
	}
	camera_update(&camera, cam_pos, cam_target);
	app->input.mouse_movement = (t_float2){};

	t_float4x4 view = ft_float4x4_view(cam_pos, camera.x, camera.y, camera.z);

	t_float3 sphere_view_coord[4];
	for (int i = 0; i < 4; ++i)
	{
		sphere_view_coord[i] = ft_float3_transform(&view, sphere_pos[i]);
	}

	int y = 0;
	while (y < out->height)
	{
		int x = 0;
		while (x < out->width)
		{
			t_float3 p;
			p.x = ((float)x + 0.5f) / (float)out->width * 2 - 1;
			p.y = ((float)y + 0.5f) / (float)out->height * 2 - 1;
			p.x *= camera.aspect;
			p.z = -1.0f;
			p = ft_float3_normalize(p);

			t_ray ray = {{}, p};
			
			float mul = 500.0f;
			t_argb32 col = 0;
			for (int i = 0; i < 4; ++i)
			{
				float m = ray_sphere_intersect(&ray, sphere_view_coord[i], rad);
				if (m > 0 && m <= mul)
				{
					mul = m;
					t_float3 hit = ft_float3_scalar(ray.direction, m);
					hit = ft_float3_add(ray.origin, hit); 
					hit = ft_float3_sub(hit, sphere_view_coord[i]);
					hit = ft_float3_normalize(hit);
					hit.x = (hit.x + 1) * 0.5f;
					hit.y = (hit.y + 1) * 0.5f;
					hit.z = (hit.z + 1) * 0.5f;
					col = (int)(hit.x * 255.0f) << 16 | (int)(hit.y * 255.0f) << 8 | (int)(hit.z * 255.0f);
				}
			}

			framebuf_put_pixel(out, (t_float3){x, y, 0.0f}, col);

			++x;
		}
		++y;
	}

	window_swap_buf(window);
	if (app->input.exit)
	{
		app_terminate(app, 0);
	}
	return (1);
}
