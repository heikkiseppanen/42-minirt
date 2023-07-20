
#include <ft/cstr.h>
#include <ft/io.h>
#include <ft/std.h>
#include <parser/parser.h>
#include <minirt.h>
#include <fcntl.h>

void	string_to_float3(char *line, t_float3 *data)
{
	while (ft_isspace(*line))
		line++;
	data->x = ft_atof(line);
	while (*line != ',')
		line++;
	line++;
	data->y = ft_atof(line);
	while (*line != ',')
		line++;
	line++;
	data->z = ft_atof(line);
	while (!ft_isspace (*line))
		line++;
}

t_err	handle_line(char *line)
{
	while (line)
	{
		if (ft_isspace(*line))
			line++;
	}
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
		if (handle_line(line))
			return (RT_FAILURE);
		free (line);
	}
	close (file_fd);
	return (RT_SUCCESS);
}
