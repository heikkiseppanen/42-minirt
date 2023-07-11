/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/11 12:35:30 by hseppane         ###   ########.fr       */
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

	offset = ((int)position.x + (int)position.y * output->width);
	offset *= sizeof(color);
	*((unsigned int *)(output->color + offset)) = color;
}


int	app_loop(t_app *app)
{
	t_window *const	window = &app->window;

	/* Clear framebuf */

	//framebuf_clear(&window->framebuffer, ARGB_NORD);

	/* Draw */

	//float fov = M_PI;
	static t_float3 pos[] = {
		{-0.25f, 0.0f, 0.0f},
		{0.25f, 0.0f, 0.0f},
		{0.0f, -0.25f, 0.0f},
	};
	float rad = 0.5f;
	t_framebuf *out = &window->framebuffer;
	const float aspect = (float)out->width / (float)out->height;

	int y = 0;
	while (y < out->height)
	{
		int x = 0;
		while (x < out->width)
		{
			t_float3 p;
			p.x = ((float)x + 0.5f) / (float)out->width * 2 - 1;
			p.y = ((float)y + 0.5f) / (float)out->height * 2 - 1;
			p.x *= aspect;
			p.z = -1.0f;
			p = ft_float3_normalize(p);

			t_ray ray = {{0,0,2.0f}, p};
			
			float mul = 500.0f;
			t_argb32 col = 0;
			for (int i = 0; i < 3; ++i)
			{
				float m = ray_sphere_intersect(&ray, pos[i], rad);
				if (m > 0 && m <= mul)
				{
					mul = m;
					t_float3 hit = ft_float3_scalar(ray.direction, m);
					hit = ft_float3_add(ray.origin, hit); 
					hit = ft_float3_sub(hit, pos[i]);
					hit = ft_float3_normalize(hit);
					hit.x = (hit.x + 1) * 0.5f;
					hit.y = (hit.y + 1) * 0.5f;
					hit.z = (hit.z + 1) * 0.5f;
					col = (int)(hit.x * 255.0f) << 16 | (int)(hit.y * 255.0f) << 8 | (int)(hit.z * 255.0f);
				}
			}

			framebuf_put_pixel(out, (t_float3){x, out->height - y, 0.0f}, col);

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
