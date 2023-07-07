/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/07 15:46:23 by hseppane         ###   ########.fr       */
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
#define ARGB_GREEN 0x00FF0000
#define ARGB_BLUE 0x000000FF
#define ARGB_NORD 0x002E3440

typedef unsigned int t_argb32;

typedef char t_bool;

#define TRUE 1
#define FALSE 0

typedef struct s_ray
{
	t_float3 origin;
	t_float3 direction;
} t_ray;

//t_argb32	ray_cast(t_ray *ray, jj

float	ray_sphere_intersect(const t_ray *ray, t_float3 position, float radius)
{
	const t_float3 sphere_to_ray = ft_float3_sub(ray->origin, position);
	const float distance = ft_float3_len(sphere_to_ray);
	float d;

	d = ft_float3_dot(ray->direction, sphere_to_ray); 
	d = d * d;
	d -= (distance * distance) - (radius * radius); 
	if (d < 0)
	{
		return -1.0f;
	}
	return 1.0f;
}

void framebuf_put_pixel(t_framebuf *output, t_float3 position, t_argb32 color)
{
	const size_t offset = (int)position.x + (int)position.y * output->width;

	*((unsigned int *)(output->color + offset)) = color;
}


int	app_loop(t_app *app)
{
	t_window *const	window = &app->window;

	/* Clear framebuf */

	framebuf_clear(&window->framebuffer, ARGB_NORD);

	/* Draw */

	float fov = M_PI;
	t_ray ray = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}};
	t_float3 pos = {0.0f, 0.0f, 5.0f};
	float rad = 1.0f;

	t_framebuf *render_target = &window->framebuffer;
	int x = 0;
	int y = 0;
	while (y < render_target->height)
	{
		while (x < render_target->width)
		{

		}
	}

	float ray_scalar = ray_sphere_intersect(&ray, pos, rad);

	if (ray_scalar < 0)
	{

	}

	window_swap_buf(window);
	if (app->input.exit)
	{
		app_terminate(app, 0);
	}
	return (1);
}
