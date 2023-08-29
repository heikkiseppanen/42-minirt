#ifndef CAMERA_H
# define CAMERA_H

#include <scene/ecs.h>
#include <app/app.h>

void	update_camera_pos(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	camera_update(t_camera *camera);
#endif