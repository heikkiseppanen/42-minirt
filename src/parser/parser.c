/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:00 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/09/26 09:50:43 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/cstr.h>
#include <ft/io.h>
#include <fcntl.h>
#include <parser/parser.h>

t_err	handle_line(t_ecs *ecs, char *line)
{
	char	**tokens;
	t_err	status;

	tokens = ft_split(line, ' ');
	status = RT_SUCCESS;
	if (!tokens)
		status = RT_FAILURE;
	else if (!ft_strncmp(tokens[0], "A", 2))
		status = deserialize_ambient(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "C", 2))
		status = deserialize_camera(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "L", 2))
		status = deserialize_light(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "sp", 3))
		status = deserialize_sphere(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		status = deserialize_plane(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		status = deserialize_cylinder(ecs, tokens);
	else if (*tokens[0] != '\n')
		status = RT_FAILURE;
	ft_strarr_del(tokens);
	return (status);
}

t_bool	path_has_extension(const char *path, const char *ext)
{
	const int	path_length = ft_strlen(path);
	const int	ext_length = ft_strlen(ext);

	if (path_length <= ext_length
		|| ft_strncmp(path + path_length - ext_length, ext, ext_length) != 0)
		return (RT_FALSE);
	return (RT_TRUE);
}

t_err	scene_parser(t_ecs *ecs, const char *file)
{
	char	*line;
	int		file_fd;
	t_err	status;

	if (!path_has_extension(file, ".rt"))
		return (RT_FAILURE);
	file_fd = open(file, O_RDONLY);
	if (file_fd <= 0)
		return (RT_FAILURE);
	status = RT_SUCCESS;
	while (status == RT_SUCCESS)
	{
		line = get_next_line(file_fd);
		if (!line)
			break ;
		if (!handle_line(ecs, line))
			status = RT_FAILURE;
		free (line);
	}
	if (!ecs->camera)
		status = RT_FAILURE;
	close (file_fd);
	return (status);
}
