/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:46:26 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/31 13:28:02 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/renderer.h"

#include "renderer/color.h"
#include "renderer/light.h"
#include "renderer/ray.h"

void	renderer_init(t_renderer *self)
{
	(void)self;
}

void	renderer_pass(t_renderer *self, const t_ecs *scene, mlx_image_t *out)
{
	unsigned int y = 0;
	while (y < out->height)
	{
		unsigned int x = 0;
		while (x < out->width)
		{
			t_float3 pixel = pix_00; 
			pixel = ft_float3_add(pixel, ft_float3_scalar(u, x));
			pixel = ft_float3_add(pixel, ft_float3_scalar(v, y));

			ray.direction = ft_float3_sub(pixel, ray.origin);
			ray.direction = ft_float3_normalize(ray.direction);

			t_rgba32 color = RGBA_BLACK;
			t_hit	hit = {};
			if (ray_cast(&ray, ecs, &hit))
			{
				t_material *mat = ecs_get_component(ecs, hit.entity, ECS_MATERIAL);

				t_color light = calculate_surface_light(&hit.position, &hit.normal, ecs);

				t_color diff_color = ft_float3_mul(mat->color, light); 
				diff_color = saturate(linear_to_srgb(diff_color));

				color = color_to_rgba32(diff_color);
			}

			mlx_put_pixel(out, x, y, color);

			++x;
		}
		++y;
	}
}
