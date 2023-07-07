/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:08:28 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/07 09:49:18 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"

#include <ft/io.h>
#include <mlx.h>

int	main(int argc, char **argv)
{
	t_app	qub3d;

	if (argc != 2)
	{
		ft_printf("Use: minirt <map_path>\n");
		return (1);
	}
	if (!app_init(&qub3d, argc, argv))
	{
		app_terminate(&qub3d, 1);
	}
	mlx_loop(qub3d.window.handle);
	return (1);
}
