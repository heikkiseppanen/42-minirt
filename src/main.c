/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:08:28 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/23 11:44:37 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"
#include "scene/ecs.h"
#include "parser/parser.h"
#include "minirt.h"

#include <ft/io.h>
#include <MLX42/MLX42.h>

#include <ft/std.h>

int	main(int argc, char **argv)
{
	t_app	miniRT;

	if (argc != 2)
	{
		// TODO Add proper argument validation
		ft_printf("Use: miniRT <scene_path>\n");
		return (1);
	}
	if (app_init(&miniRT, argc, argv))
	{
		mlx_loop(miniRT.window);
	}
	app_close_hook(&miniRT);
	return (1);
}
