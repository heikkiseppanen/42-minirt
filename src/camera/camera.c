#include <camera/camera.h>
#include <scene/ecs.h>
#include <ft/cstr.h>

void	camera_update(t_camera *camera, __attribute__((unused))t_float3 position)
{
	camera->z = ft_float3_scalar(camera->pivot, -1);
	camera->z = ft_float3_normalize(camera->z);
	camera->y = (t_float3){0.0, 1.0, 0.0};
	camera->x = ft_float3_cross(camera->y, camera->z);
	camera->x = ft_float3_normalize(camera->x);
	camera->y = ft_float3_cross(camera->z, camera->x);
}

void	update_camera_pos(t_app *app, t_camera *camera, t_float3 *cam_pos)
{
	float	speed;
	t_float3 offset;

	speed = 2;
	ft_memset(&offset, 0, sizeof(t_float3));
	if (app->input.w)
		offset = ft_float3_sub(offset, ft_float3_scalar(camera->z, speed));
	if (app->input.s)
		offset = ft_float3_add(offset, ft_float3_scalar(camera->z, speed));
	if (app->input.a)
		offset = ft_float3_sub(offset, ft_float3_scalar(camera->x, speed));
	if (app->input.d)
		offset = ft_float3_add(offset, ft_float3_scalar(camera->x, speed));
	if (app->input.space)
		offset = ft_float3_add(offset, ft_float3_scalar(camera->y, speed));
	if (app->input.ctrl)
		offset = ft_float3_sub(offset, ft_float3_scalar(camera->y, speed));
	if (app->input.left_button)
	{
		camera->pivot = ft_float3_rot_y(camera->pivot, app->input.mouse_movement.x * app->window->delta_time);
		camera->pivot = ft_float3_rot_axis(camera->pivot, camera->x, app->input.mouse_movement.y * app->window->delta_time);
	}
	if (app->input.right_button)
	{
		offset = ft_float3_add(offset, ft_float3_scalar(camera->x, app->input.mouse_movement.x * speed));
		offset = ft_float3_add(offset, ft_float3_scalar(camera->y, -app->input.mouse_movement.y * speed));
	}
	offset = ft_float3_scalar(offset, app->window->delta_time);
	*cam_pos = ft_float3_add(*cam_pos, offset);
	// camera->pivot = ft_float3_add(camera->pivot, offset);
	camera_update(camera, *cam_pos);
}
