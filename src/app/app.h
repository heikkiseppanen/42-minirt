/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:08:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 12:34:27 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "window/window.h"
# include "input/input.h"

typedef struct s_app
{
	t_window	window;
	t_input		input;
}	t_app;

int	app_init(t_app *instance, int argc, char **argv);
int	app_terminate(t_app *instance, int exit_code);

int	app_loop(t_app *app);

#endif
