/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:35:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/12 11:31:48 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "minirt.h"
# include "scene/ecs.h"

# include <MLX42/MLX42.h>

# define PREVIEW_CHUNK_SIZE 8

typedef struct s_renderer
{
	int	chunk_size;
}	t_renderer;

void	renderer_init(t_renderer *self);

void	renderer_pass(t_renderer *self, const t_ecs *scene, mlx_image_t *out);

#endif
