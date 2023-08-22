#include <camera/camera.h>


void	update_camera_pos(t_app *app, t_float3 *camera_pos)
{
	if (app->input.w)
	{
		camera_pos->z--;
	}
	if (app->input.s)
	{
		camera_pos->z++;
	}
	if (app->input.a)
	{
		camera_pos->x--;
	}
	if (app->input.d)
	{
		camera_pos->x++;
	}
	if (app->input.space)
	{
		camera_pos->y++;
	}
	if (app->input.ctrl)
	{
		camera_pos->y--;
	}
}

