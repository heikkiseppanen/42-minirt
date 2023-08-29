/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:46:26 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/21 09:40:31 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/renderer.h"

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

t_err	render_state_init(t_render_state *rs, t_ecs *scene_data, int width, int height)
{

}

void	render_state_clear(t_render_state *rs);

void	render_pass(t_render_state *state, t_ecs *scene_data, mlx_image_t *out)
{
	int	x;
	int	y;

	while (y < (int)out->height)
	{
		while (x < (int)out->width)
		{

		}
	}
}
