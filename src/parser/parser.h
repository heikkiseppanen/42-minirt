#ifndef PARSER_H
# define PARSER_H

#include <ft/math.h>
#include <minirt.h>

typedef struct s_ambient
{
	float		ratio;
	t_float3	color;
}	t_ambient;

typedef struct s_camera
{
	t_float3	point;
	t_float3	orientation;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_float3	point;
	float		ratio;
	t_float3	color; //!UNUSED IN MANDATORY PART
}	t_light;

typedef struct s_sphere
{
	t_float3	point;
	float		diameter;
	t_float3	color;
}	t_sphere;

typedef struct s_planeb
{
	t_float3	point;
	t_float3	normal;
	t_float3	color;
}	t_planeb;

typedef struct s_cylinder
{
	t_float3	point;
	t_float3	normal;
	float		diameter;
	float		height;
	t_float3	color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_light		light;
	t_camera	camera;
	t_sphere	*sphere;
	t_planeb	*planeb;
	t_cylinder	*cylinder;
}	t_scene;

t_err	scene_parser(const char *file);
void	string_to_float3(char *line, t_float3 *data);



#endif