#ifndef CAMERA_H
# define CAMERA_H

#include <scene/ecs.h>
#include <app/app.h>

void	update_camera(t_app *app, t_camera *camera, t_float3 *cam_pos);
void	reorient_camera(t_camera *camera);
#endif