/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:34 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/31 14:51:37 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera/camera.h>

static void	update_camera_rot(t_app *app, t_camera *camera)
{
	float		sens;
	t_float2	input;
	float		pitch_new;
	float		pitch_limit;

	sens = 0.03;
	input.x = app->input.mouse_movement.x * sens * app->window->delta_time;
	input.y = app->input.mouse_movement.y * sens * app->window->delta_time;
	pitch_new = camera->pitch + input.y;
	pitch_limit = ft_rad(90);
	if (pitch_new < pitch_limit && pitch_new > -pitch_limit)
	{
		camera->pitch += input.y;
		camera->pivot = ft_float3_rot_axis(camera->pivot, camera->x, input.y);
	}
	camera->pivot = ft_float3_rot_y(camera->pivot, input.x);
}

void	camera_keyboard_input(t_app *app, t_camera *camera, t_float3 *cam_pos)
{
	float	speed;

	speed = camera->speed;
	if (app->input.w)
		*cam_pos = ft_float3_sub(*cam_pos, ft_float3_scalar(camera->z, speed));
	if (app->input.s)
		*cam_pos = ft_float3_add(*cam_pos, ft_float3_scalar(camera->z, speed));
	if (app->input.a)
		*cam_pos = ft_float3_sub(*cam_pos, ft_float3_scalar(camera->x, speed));
	if (app->input.d)
		*cam_pos = ft_float3_add(*cam_pos, ft_float3_scalar(camera->x, speed));
	if (app->input.space)
		*cam_pos = ft_float3_add(*cam_pos, ft_float3_scalar(camera->y, speed));
	if (app->input.ctrl)
		*cam_pos = ft_float3_sub(*cam_pos, ft_float3_scalar(camera->y, speed));
}

void	camera_mouse_input(t_app *app, t_camera *camera, t_float3 *pos)
{
	t_float2	input;
	float		max_speed;
	float		min_speed;

	max_speed = 6;
	min_speed = 0.1;
	if (camera->speed < max_speed && app->input.scroll > 0.0)
		camera->speed += 0.05;
	if (camera->speed > min_speed && app->input.scroll < 0.0)
		camera->speed -= 0.05;
	if (app->input.left_button)
		update_camera_rot(app, camera);
	if (app->input.right_button)
	{
		input.x = app->input.mouse_movement.x * camera->speed;
		input.y = app->input.mouse_movement.y * camera->speed;
		*pos = ft_float3_add(*pos, ft_float3_scalar(camera->x, input.x));
		*pos = ft_float3_add(*pos, ft_float3_scalar(camera->y, input.y));
	}
	app->input.scroll = 0;
}
