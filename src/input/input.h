/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/25 14:44:12 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <MLX42/MLX42.h>
# include <ft/math.h>

typedef struct s_input
{
	char		exit;
	char		left_button;
	char		right_button;
	t_float2	mouse_position;
	t_float2	mouse_movement;
}	t_input;

void	input_init(t_input *input, mlx_t *window);

#endif
