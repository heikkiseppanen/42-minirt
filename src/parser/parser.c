/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:00 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:02 by ttalvenh         ###   ########.fr       */
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
	else if (!ft_strncmp(tokens[0], "A", sizeof(tokens[0])))
		status = deserialize_ambient(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "C", sizeof(tokens[0])))
		status = deserialize_camera(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "L", sizeof(tokens[0])))
		status = deserialize_light(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "sp", sizeof(tokens[0])))
		status = deserialize_sphere(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "pl", sizeof(tokens[0])))
		status = deserialize_plane(ecs, tokens);
	else if (!ft_strncmp(tokens[0], "cy", sizeof(tokens[0])))
		status = deserialize_cylinder(ecs, tokens);
	else if (*tokens[0] != '\n')
		status = RT_FAILURE;
	ft_strarr_del(tokens);
	return (status);
}

t_err	scene_parser(t_ecs *ecs, const char *file)
{
	char	*line;
	int		file_fd;

	if (ft_strlen(file) >= 3
		&& ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 3))
		return (RT_FAILURE);
	file_fd = open(file, O_RDONLY);
	if (file_fd <= 0)
		return (RT_FAILURE);
	while (1)
	{
		line = get_next_line(file_fd);
		if (!line)
			break ;
		if (!handle_line(ecs, line))
		{	
			free (line);
			return (RT_FAILURE);
		}
		free (line);
	}
	if (!ecs->camera)
		return (RT_FAILURE);
	close (file_fd);
	return (RT_SUCCESS);
}
