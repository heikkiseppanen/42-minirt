/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:35:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/27 10:47:45 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# define CHUNK_SIZE 64

# include "minirt.h"
# include "scene/ecs.h"

# include <MLX42/MLX42.h>

typedef struct s_renderer
{
	int		chunk_size;
	t_buf	rays;
}	t_renderer;

t_err	renderer_init(
			t_renderer *r,
			const t_ecs *scene,
			const mlx_image_t *target
		);

void	renderer_del(t_renderer *r);

void	render_pass(t_renderer *r, const t_ecs *scene, mlx_image_t *out);

#endif
