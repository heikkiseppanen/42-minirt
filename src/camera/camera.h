/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:26 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/31 14:51:28 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <scene/ecs.h>
# include <app/app.h>

void	update_camera(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	reorient_camera(t_camera *camera);
void	camera_keyboard_input(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	camera_mouse_input(t_app *app, t_camera *camera, t_float3 *pos);
#endif
