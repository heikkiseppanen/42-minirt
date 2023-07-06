/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:09:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 17:01:49 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include "window/window.h"

#include <mlx.h>
#include <stdlib.h>

int	app_init(t_app *empty, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (!window_init(&empty->window, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF"))
	{
		return (0);
	}
	mlx_loop_hook(empty->window.mlx_handle, app_loop, empty);
	mlx_hook(empty->window.mlx_window, ON_DESTROY, 0, app_terminate, empty);
	input_init(&empty->input, empty->window.mlx_window);
	return (1);
}

int	app_terminate(t_app *instance, int exit_code)
{
	window_del(&instance->window);
	exit(exit_code);
	return (1);
}

int	app_loop(t_app *app)
{
	t_window *const	window = &app->window;

	window_swap_buf(window);
	if (app->input.exit)
	{
		app_terminate(app, 0);
	}
	return (1);
}
