/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:46:26 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/11 13:14:19 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/renderer.h"
#include "renderer/color.h"
#include "renderer/light.h"
#include "ray/ray.h"

#include "camera/camera.h"

static void	draw_quad(t_int2 pos, int size, t_rgba32 color, mlx_image_t *out)
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

void	renderer_init(t_renderer *self)
{
	self->chunk_size = PREVIEW_CHUNK_SIZE;
}

void	renderer_pass(t_renderer *self, const t_ecs *scene, mlx_image_t *out)
{
	t_camera *camera = ecs_get_component(scene, scene->camera, ECS_CAMERA);
	t_float3 *position = ecs_get_component(scene, scene->camera, ECS_POSITION);
	t_ray	ray;
	t_int2	pixel;
	t_bool	is_sample_row;

	if (self->chunk_size == 0)
		return ;
	is_sample_row = RT_TRUE;
	pixel = (t_int2){};
	while (pixel.y < (int)out->height)
	{
		if (is_sample_row && self->chunk_size < PREVIEW_CHUNK_SIZE)
			pixel.x = self->chunk_size;
		else
			pixel.x = 0;
		while (pixel.x < (int)out->width)
		{
			ray = camera_get_pixel_ray(camera, position, pixel.x, pixel.y);

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
			draw_quad(pixel, self->chunk_size, final_color, out);
			pixel.x += self->chunk_size;
			if (is_sample_row && self->chunk_size < PREVIEW_CHUNK_SIZE)
				pixel.x += self->chunk_size;
		}
		is_sample_row = !is_sample_row;
		pixel.y += self->chunk_size;
	}
	self->chunk_size /= 2;
}
