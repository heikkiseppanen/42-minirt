#include <camera/camera.h>
#include <scene/ecs.h>

void	update_camera_pos(t_app *app, t_ecs *ecs)
{
	__attribute__((unused))t_camera *camera = ecs_get_component(ecs, ecs->camera, ECS_CAMERA);
	t_float3 *camera_pos = ecs_get_component(ecs, ecs->camera, ECS_POSITION);
	float	speed;

	speed = 0.1;
	if (app->input.w)
	{
		camera_pos->z -= speed;
		camera->pivot.z -= speed;
	}
	if (app->input.s)
	{
		camera_pos->z += speed;
		camera->pivot.z += speed;
	}
	if (app->input.a)
	{
		camera_pos->x -= speed;
		camera->pivot.x -= speed;
	}
	if (app->input.d)
	{
		camera_pos->x += speed;
		camera->pivot.x += speed;
	}
	if (app->input.space)
	{
		camera_pos->y += speed;
		camera->pivot.y += speed;
	}
	if (app->input.ctrl)
	{
		camera_pos->y -= speed;
		camera->pivot.y -= speed;
	}
}

