/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:26 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/14 11:54:14 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "scene/ecs.h"
# include "app/app.h"
# include "ray/ray.h"
typedef struct s_camera
{
	float		fov;
	float		pitch;
	float		speed;
	t_float3	pix_00;
	t_float3	u;
	t_float3	v;
	t_float3	pivot;
	t_float3	x;
	t_float3	y;
	t_float3	z;
}	t_camera;

void	update_camera(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	reorient_camera(t_camera *camera);

void	camera_keyboard_input(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	camera_mouse_input(t_app *app, t_camera *camera, t_float3 *pos);

t_ray	camera_get_pixel_ray(t_camera *self, t_float3 *position, int x, int y);
#endif
