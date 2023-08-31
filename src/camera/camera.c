#include <camera/camera.h>
#include <scene/ecs.h>
#include <ft/cstr.h>
#include <ft/math.h>
#include <math.h>

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
	float	speed;

	speed = 2 * app->window->delta_time;
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
	if (app->input.left_button)
		update_camera_rot(app, camera);
	if (app->input.right_button)
	{
		*cam_pos = ft_float3_add(*cam_pos, ft_float3_scalar(camera->x, app->input.mouse_movement.x * speed));
		*cam_pos = ft_float3_add(*cam_pos, ft_float3_scalar(camera->y, -app->input.mouse_movement.y * speed));
	}
	reorient_camera(camera);
	calc_canvas(app->framebuffer, camera, cam_pos);
}
