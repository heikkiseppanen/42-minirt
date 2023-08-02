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

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (RT_FAILURE);
	if (!ft_strncmp(tokens[0], "A", sizeof(tokens[0])))
		return (deserialize_ambient(ecs, tokens) + free_array(tokens));
	if (!ft_strncmp(tokens[0], "C", sizeof(tokens[0])))
		return (deserialize_camera(ecs, tokens) + free_array(tokens));
	if (!ft_strncmp(tokens[0], "L", sizeof(tokens[0])))
		return (deserialize_light(ecs, tokens) + free_array(tokens));
	if (!ft_strncmp(tokens[0], "sp", sizeof(tokens[0])))
		return (deserialize_sphere(ecs, tokens) + free_array(tokens));
	if (!ft_strncmp(tokens[0], "pl", sizeof(tokens[0])))
		return (deserialize_plane(ecs, tokens) + free_array(tokens));
	if (!ft_strncmp(tokens[0], "cy", sizeof(tokens[0])))
		return (deserialize_cylinder(ecs, tokens) + free_array(tokens));
	if (*tokens[0] != '\n')
		return (parse_error(tokens) + free_array(tokens));
	return (RT_SUCCESS + free_array(tokens));
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
			break ;
		if (!handle_line(ecs, line))
		{	
			free (line);
			return (RT_FAILURE);
		}
		free (line);
	}
	close (file_fd);
	return (RT_SUCCESS);
}
