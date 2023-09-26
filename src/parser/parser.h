/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:09 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:12 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene/ecs.h"
# include <ft/math.h>
# include <minirt.h>

t_err	scene_parser(t_ecs *ecs, const char *file);
t_err	check_commas(const char *line);

//deserialize_geometry
t_err	deserialize_sphere(t_ecs *ecs, char **tokens);
t_err	deserialize_plane(t_ecs *ecs, char **tokens);
t_err	deserialize_cylinder(t_ecs *ecs, char **tokens);

//deserialize_camera_light
t_err	deserialize_ambient(t_ecs *ecs, char **tokens);
t_err	deserialize_camera(t_ecs *ecs, char **tokens);
t_err	deserialize_light(t_ecs *ecs, char **tokens);

//deserialize_component
t_err	get_point(char *token, t_float3 *point);
t_err	get_color(char *token, t_float3 *color);
t_err	get_normal(char *token, t_float3 *normal);
t_err	get_radius(char *token, float *radius);
t_err	get_height(char *token, float *height);

//utils
t_err	parse_error(char **tokens);
int		array_2d_length(char **array_2d);
int		free_array(char **arr);
t_bool	ft_is_float(const char *str);
t_err	string_to_float3(const char *str, t_float3 *float3);

//utils2
t_bool	color_valid(t_float3 *color);
t_bool	light_ratio_valid(float *ratio);
t_bool	normal_valid(t_float3 *normal);

#endif
