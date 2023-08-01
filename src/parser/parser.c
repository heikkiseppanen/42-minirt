#include <ft/cstr.h>
#include <ft/io.h>
#include <ft/std.h>
#include <parser/parser.h>
#include <minirt.h>
#include <fcntl.h>

t_err	parse_error(char **split_line)
{
	ft_free_array(split_line);
	printf("Line error\n");
	return (RT_FAILURE);
}

t_err	deserialize_sphere(t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[2]))
		return (parse_error(split_line));
	geometry.data.sphere.radius = 2 / ft_atof(split_line[2]);
	if (!string_to_float3(split_line[3], &material.color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY);
	ecs_add_component(ecs, entity, &material, ECS_MATERIAL);
	return (RT_SUCCESS);
}

t_err	deserialize_plane(t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[2], &geometry.data.plane.normal))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[3], &material.color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &material, ECS_MATERIAL);
	ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY);
	return (RT_SUCCESS);
}

t_err	deserialize_cylinder(t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_material	material;
	t_geometry	geometry;

	if (array_2d_length(split_line) != 6)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[2], &geometry.data.cylinder.normal))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[3]))
		return (parse_error(split_line));
	geometry.data.cylinder.radius = 2 / ft_atof(split_line[3]);
	if (!ft_is_float(split_line[4]))
		return (parse_error(split_line));
	geometry.data.cylinder.height = ft_atof(split_line[4]);
	if (!string_to_float3(split_line[5], &material.color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &material, ECS_MATERIAL);
	ecs_add_component(ecs, entity, &geometry, ECS_GEOMETRY);
	return (RT_SUCCESS);
}

t_err	deserialize_ambient(t_ecs *ecs, char **split_line)
{
	t_id	entity;
	t_light	ambient;

	if (array_2d_length(split_line) != 3)
		return (parse_error(split_line));
	if (!ft_is_float(split_line[1]))
		return (parse_error(split_line));
	ambient.attenuation = ft_atof(split_line[1]);
	if (!string_to_float3(split_line[2], &ambient.color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &ambient, ECS_LIGHT);
	return (RT_SUCCESS);
}

t_err	deserialize_light(t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_light		light;

	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[2]))
		return (parse_error(split_line));
	light.attenuation = ft_atof(split_line[2]);
	if (!string_to_float3(split_line[3], &light.color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &light, ECS_LIGHT);
	return (RT_SUCCESS);
}

t_err	deserialize_camera(t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_camera	camera;

	ft_memset(&camera, 0, sizeof(camera));
	camera.x.x = 1;
	camera.y.y = 1;
	camera.z.z = 1;
	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[2], &camera.pivot))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[3]))
		return (parse_error(split_line));
	camera.fov = ft_atof(split_line[3]);
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_POSITION);
	ecs_add_component(ecs, entity, &camera, ECS_CAMERA);
	return (RT_SUCCESS);
}

t_err	handle_line(t_ecs *ecs, char *line)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (RT_FAILURE);
	if (!ft_strncmp(split_line[0], "A", 1))
		printf("A\n");
	else if (!ft_strncmp(split_line[0], "C", 1))
		printf("C\n");
	else if (!ft_strncmp(split_line[0], "L", 1))
		printf("L\n");
	else if (!ft_strncmp(split_line[0], "sp", 2))
		return (deserialize_sphere(ecs, split_line));
	else if (!ft_strncmp(split_line[0], "pl", 2))
		return (deserialize_plane(ecs, split_line));
	else if (!ft_strncmp(split_line[0], "cy", 2))
		return (deserialize_cylinder(ecs, split_line));
	else if (*split_line[0] != '\n')
		return (parse_error(split_line));
	ft_free_array(split_line);

	return (RT_SUCCESS);
}

t_err	scene_parser(t_ecs *ecs, const char *file)
{
	char	*line;
	int		file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd <= 0)
		return (RT_FAILURE);
	while (1)
	{
		line = get_next_line(file_fd);
		if (!line)
			break;
		if (!handle_line(ecs, line))
			return (RT_FAILURE);
		free (line);
	}
	close (file_fd);
	return (RT_SUCCESS);
}
 
 