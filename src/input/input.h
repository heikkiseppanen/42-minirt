/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:35:09 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <MLX42/MLX42.h>
# include <ft/math.h>

typedef struct s_input
{
	char		escape;
	char		left_button;
	char		right_button;
	char		w;
	char		s;
	char		a;
	char		d;
	float		scroll;
	char		ctrl;
	char		space;
	t_float2	mouse_position;
	t_float2	mouse_movement;
}	t_input;

void	input_init(t_input *input, mlx_t *window);

#endif
