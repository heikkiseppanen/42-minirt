/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:08:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/14 08:53:08 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input/input.h"

#include "window/window.h"

#ifdef __linux__
# include "input/linux/keycodes.h"
#else
# include "input/macos/keycodes.h"
#endif

#include <mlx.h>
#include <ft/io.h>

static int	keydown_hook(int keycode, t_input *input)
{
	ft_printf("key: %i\n", keycode);
	if (keycode == KEY_ESCAPE)
		input->exit = 1;
	return (1);
}

static int	mousemove_hook(int x, int y, t_input *input)
{
	const t_float2	new_pos = {x, y};

	ft_printf("mouse x %i y %i\n", x, y);
	input->mouse_movement = ft_float2_sub(input->mouse_position, new_pos);
	input->mouse_position = new_pos;
	return (1);
}

static int	mousedown_hook(int button, int x, int y, t_input *input)
{
	(void)x;
	(void)y;
	(void)input;
	if (button == MOUSE_LEFT)
	{
		input->left_button = 1;
	}
	ft_printf("mouse down %i\n", button);
	return (1);
}

static int	mouseup_hook(int button, int x, int y, t_input *input)
{
	(void)x;
	(void)y;
	(void)input;
	if (button == MOUSE_LEFT)
	{
		input->left_button = 0;
	}
	ft_printf("mouse up %i\n", button);
	return (1);
}

void	input_init(t_input *empty, void *mlx_window)
{
	*empty = (t_input){};
	mlx_hook(mlx_window, ON_KEYDOWN, 1L << 0 | 1L << 1 | 1L << 14, keydown_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEDOWN, 1L << 2 | 1L << 3 | 1L << 8 | 1L << 9 | 1L << 10 | 1L << 6 | 1 << 13 | 1L << 14, mousedown_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEUP, 1L << 2 | 1L << 3 | 1L << 8 | 1L << 9 | 1L << 10 | 1L << 6 | 1 << 13 | 1L << 14, mouseup_hook, empty);
	mlx_hook(mlx_window, ON_MOUSEMOVE, 1L << 0, mousemove_hook, empty);
}
