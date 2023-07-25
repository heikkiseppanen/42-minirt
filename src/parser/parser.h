#ifndef PARSER_H
# define PARSER_H

# include "scene/ecs.h"
# include <ft/math.h>
# include <minirt.h>


t_err	scene_parser(t_ecs *ecs, const char *file);

//utils
int		array_2d_length(char **array_2d);
int		ft_free_array(char **arr);
t_bool	ft_is_float(const char *str);
t_err	string_to_float3(const char *str, t_float3 *float3);

#endif