
#include <ft/cstr.h>
#include <ft/io.h>
#include <ft/std.h>
#include <parser/parser.h>
#include <minirt.h>
#include <fcntl.h>

t_err	valid_string_float3 (char *line)
{
	int	i;
	int	decimal;
	int parameters;

	i = 0;
	decimal = 0;
	parameters = 0;
	
	while (line[i] && !ft_isspace(line[i])) 
	{
		if (!ft_isdigit(line[i]))
			return (RT_FAILURE);
		while (line[i] != ',')
		{
			if (line[i] == '.')
				decimal++;
			if ((!ft_isdigit(line[i]) && line[i] != '.') || decimal > 1)
				return (RT_FAILURE);
			i++;
		}
		decimal--;
		parameters++;
		i++;
	}
	if (parameters != 3)
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	string_to_float3(char *line, t_float3 *data)
{
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
	return (RT_SUCCESS);
}

t_err	handle_line(char *line)
{
	while (ft_isspace(*line))
		line++;

	// if (!ft_strncmp(line, "A", 1))
	// 	printf("A\n");
	// if (!ft_strncmp(line, "C", 1))
	// 	printf("C\n");
	// if (!ft_strncmp(line, "L", 1))
	// 	printf("L\n");
	// if (!ft_strncmp(line, "sp", 2))
	// 	printf("sp\n");
	// if (!ft_strncmp(line, "pl", 2))
	// 	printf("pl\n");
	// if (!ft_strncmp(line, "cy", 2))
	// 	printf("cy\n");
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
 
 