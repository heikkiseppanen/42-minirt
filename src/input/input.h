/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:27:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/14 08:53:19 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <ft/math.h>

typedef struct s_input
{
	char		exit;
	char		left_button;
	t_float2	mouse_position;
	t_float2	mouse_movement;
}	t_input;

void	input_init(t_input *empty, void *mlx_window);

//void	input_key_pressed(t_input *empty, enum e_key key);

#endif
