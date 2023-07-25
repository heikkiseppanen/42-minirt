
#include <ft/cstr.h>
#include <ft/io.h>
#include <ft/std.h>
#include <parser/parser.h>
#include <minirt.h>
#include <fcntl.h>

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (*arr != NULL)
	{
		free(*arr++);
		i++;
	}
	free(arr - i);
}

t_err	parse_error(char **split_line)
{
	ft_free_array(split_line);
	printf("Line error\n");
	return (RT_FAILURE);
}

int		array_2d_length(char **array_2d)
{
	int	i;

	i = 0;
	while (array_2d[i])
		i++;
	return (i);
}


t_err	parse_sphere(char **split_line)
{
	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	return (RT_SUCCESS);
}

t_err	parse_plane(char **split_line)
{
	if (array_2d_length(split_line) != 4)
		return (parse_error(split_line));
	return (RT_SUCCESS);
}

t_err	parse_cylinder(char **split_line)
{
	if (array_2d_length(split_line) != 6)
		return (parse_error(split_line));
	return (RT_SUCCESS);
}

t_err	handle_line(char *line)
{
	char **split_line;

	split_line = ft_split(line, ' ');
	if (!ft_strncmp(split_line[0], "A", 1))
		printf("A\n");
	else if (!ft_strncmp(split_line[0], "C", 1))
		printf("C\n");
	else if (!ft_strncmp(split_line[0], "L", 1))
		printf("L\n");
	else if (!ft_strncmp(split_line[0], "sp", 2))
		return (parse_sphere(split_line));
	else if (!ft_strncmp(split_line[0], "pl", 2))
		return (parse_plane(split_line));
	else if (!ft_strncmp(split_line[0], "cy", 2))
		return (parse_cylinder(split_line));
	else if (*split_line[0] != '\n')
		return (parse_error(split_line));
	ft_free_array(split_line);

	return (RT_SUCCESS);
}

t_err	scene_parser(const char *file)
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
		if (!handle_line(line))
			return (RT_FAILURE);
		free (line);
	}
	close (file_fd);
	return (RT_SUCCESS);
}
 
 