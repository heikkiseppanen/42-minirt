/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:08:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/15 11:37:47 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"

#include <MLX42/MLX42.h>
#include <ft/io.h>

static void	key_hook(mlx_key_data_t data, void *param)
{
	t_input *const	i = param;

	if (data.key == MLX_KEY_ESCAPE)
		i->escape = (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_W)
		i->w = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_A)
		i->a = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_S)
		i->s = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_D)
		i->d = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_SPACE)
		i->space = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
	if (data.key == MLX_KEY_LEFT_CONTROL)
		i->ctrl = (data.action == MLX_REPEAT) || (data.action == MLX_PRESS);
}

static void	cursor_hook(double x, double y, void *param)
{
	t_input *const	input = param;
	const t_float2	new_pos = {x, y};

	input->mouse_movement = ft_float2_sub(input->mouse_position, new_pos);
	input->mouse_position = new_pos;
}

static void	mouse_hook(
	mouse_key_t button,
	action_t action,
	modifier_key_t mods,
	void *param)
{
	t_input *const	input = param;

	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
		input->left_button = (action == MLX_PRESS);
	else if (button == MLX_MOUSE_BUTTON_RIGHT)
		input->right_button = (action == MLX_PRESS);
}

static void	scroll_hook(
	double xdelta,
	double ydelta,
	void *param)
{
	t_input *const	input = param;

	input->scroll = ydelta;
	(void)xdelta;
}

void	input_init(t_input *input, mlx_t *window)
{
	*input = (t_input){};
	mlx_mouse_hook(window, mouse_hook, input);
	mlx_cursor_hook(window, cursor_hook, input);
	mlx_key_hook(window, key_hook, input);
	mlx_scroll_hook(window, scroll_hook, input);
}
