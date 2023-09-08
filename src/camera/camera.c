/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:18 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/08 12:30:04 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera/camera.h>
#include <scene/ecs.h>
#include <ft/cstr.h>
#include <ft/math.h>
#include <math.h>

void	calc_canvas(mlx_image_t *const out, t_camera *camera, t_float3 *cam_pos)
{
	float	aspect_ratio;
	float	dx;
	float	dy;

	aspect_ratio = (float)out->height / (float)out->width;
	dx = tanf(ft_rad(camera->fov / 2));
	dy = dx * aspect_ratio;
	camera->u = ft_float3_scalar(camera->x, 2 * dx / out->width);
	camera->v = ft_float3_scalar(camera->y, -2 * dy / out->height);
	camera->pix_00 = ft_float3_sub(*cam_pos, camera->z);
	camera->pix_00 = ft_float3_add(
			camera->pix_00,
			ft_float3_scalar(camera->x, -dx));
	camera->pix_00 = ft_float3_add(
			camera->pix_00,
			ft_float3_scalar(camera->y, dy));
	camera->pix_00 = ft_float3_add(
			camera->pix_00,
			ft_float3_scalar(camera->u, 0.5f));
	camera->pix_00 = ft_float3_add(
			camera->pix_00,
			ft_float3_scalar(camera->v, 0.5f));
}

void	reorient_camera(t_camera *camera)
{
	camera->z = ft_float3_scalar(camera->pivot, -1);
	camera->z = ft_float3_normalize(camera->z);
	camera->y = (t_float3){0.0, 1.0, 0.0};
	camera->x = ft_float3_cross(camera->y, camera->z);
	camera->x = ft_float3_normalize(camera->x);
	camera->y = ft_float3_cross(camera->z, camera->x);
}

void	update_camera(t_app *app, t_camera *camera, t_float3 *cam_pos)
{
	camera_keyboard_input(app, camera, cam_pos);
	camera_mouse_input(app, camera, cam_pos);
	reorient_camera(camera);
	calc_canvas(app->framebuffer, camera, cam_pos);
}

t_ray	camera_get_pixel_ray(t_camera *self, t_float3 *position, int x, int y)
{
	t_ray ray;

	ray.origin = *position;
	ray.direction = self->pix_00; 
	ray.direction = ft_float3_add(ray.direction, ft_float3_scalar(self->u, x));
	ray.direction = ft_float3_add(ray.direction, ft_float3_scalar(self->v, y));
	ray.direction = ft_float3_sub(ray.direction, ray.origin);
	ray.direction = ft_float3_normalize(ray.direction);
	return (ray);
}
