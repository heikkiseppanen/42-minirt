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

t_err	parse_sphere(__attribute__((unused)) t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_float3	color;
	__attribute__((unused)) float		radius;

	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[2]))
		return (parse_error(split_line));
	radius = ft_atof(split_line[2]);
	if (!string_to_float3(split_line[3], &color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_TRANSFORM);
	
	return (RT_SUCCESS);
}

t_err	parse_plane(__attribute__((unused)) t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_float3	color;
	t_float3	normal;

	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[2], &normal))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[3], &color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_TRANSFORM);


	return (RT_SUCCESS);
}

t_err	parse_cylinder(__attribute__((unused)) t_ecs *ecs, char **split_line)
{
	t_id		entity;
	t_float3	point;
	t_float3	color;
	t_float3	normal;
	__attribute__((unused))float		diameter;
	__attribute__((unused))float		height;

	if (array_2d_length(split_line) != 6)
		return (parse_error(split_line));
	if (!string_to_float3(split_line[1], &point))
		return (parse_error(split_line));
	if (!string_to_float3(split_line[2], &normal))
		return (parse_error(split_line));
	if (!ft_is_float(split_line[3]))
		return (parse_error(split_line));
	diameter = ft_atof(split_line[3]);
	if (!ft_is_float(split_line[4]))
		return (parse_error(split_line));
	height = ft_atof(split_line[4]);
	if (!string_to_float3(split_line[5], &color))
		return (parse_error(split_line));
	entity = ecs_entity_create(ecs);
	if (!entity)
		return (parse_error(split_line));
	ecs_add_component(ecs, entity, &point, ECS_TRANSFORM);


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
		return (parse_sphere(ecs, split_line));
	else if (!ft_strncmp(split_line[0], "pl", 2))
		return (parse_plane(ecs, split_line));
	else if (!ft_strncmp(split_line[0], "cy", 2))
		return (parse_cylinder(ecs, split_line));
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
 
 