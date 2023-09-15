/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:08:28 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:57:17 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app/app.h"
#include "minirt.h"

#include <MLX42/MLX42.h>

#include <ft/std.h>

int	main(int argc, char **argv)
{
	t_app	minirt;
	t_err	status;

	status = app_init(&minirt, argc, argv);
	if (status == RT_SUCCESS)
	{
		mlx_loop(minirt.window);
	}
	app_terminate(&minirt);
	if (status == RT_FAILURE)
		return (1);
	return (0);
}
