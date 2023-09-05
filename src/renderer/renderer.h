/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:35:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/05 11:52:06 by hseppane         ###   ########.fr       */
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
	int		pass;
	int		start_height;
}	t_renderer;

typedef struct s_chunk
{
	int	x;
	int	y;
	int	size;
}	t_chunk;

void	renderer_init(t_renderer *self);

void	renderer_pass(t_renderer *self, const t_ecs *scene, mlx_image_t *out);

#endif

// 0, 0, 8
//1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
//
// 1, 4, 8
//1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 
//
//2, 4 
//1 0 1 0 1 0 1 0 1 0 0 0 1 0 0 0 
//
//1, 2
// 1 1 1 1 R C C C 1 1 1 1 R C C C 
// 1 1 1 1 2 2 2 2 1 1 1 1 2 2 2 2 
//
// 1 1 R C 2 2 R C 1 1 1 1 2 2 2 2 
// 1 1 3 3 2 2 3 3 1 1 1 1 2 2 2 2 
//
