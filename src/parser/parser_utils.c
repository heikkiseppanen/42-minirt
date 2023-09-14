/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttalvenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:28:17 by ttalvenh          #+#    #+#             */
/*   Updated: 2023/08/01 18:28:20 by ttalvenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/cstr.h>
#include <ft/std.h>
#include <stdio.h>
#include <parser/parser.h>

int	array_2d_length(char **array_2d)
{
	int	i;

	i = 0;
	while (array_2d[i])
	{
		i++;
	}
	return (i);
}

t_bool	color_valid(t_float3 *color)
{
	if ((color->x < 0.0 || color->x > 255.0)
		|| (color->y < 0.0 || color->y > 255)
		|| (color->z < 0.0 || color->z > 255.0))
		return (RT_FALSE);
	return (RT_SUCCESS);
}

t_bool	normal_valid(t_float3 *normal)
{
	if (!normal->x && !normal->y && !normal->z)
		return (RT_FAILURE);
	return (RT_SUCCESS);
}

t_err	string_to_float3(const char *str, t_float3 *float3)
{
	int		i;
	char	**str_split;

	i = 0;
	str_split = ft_split(str, ',');
	if (!str_split || array_2d_length(str_split) != 3)
	{
		ft_strarr_del(str_split);
		return (RT_FAILURE);
	}
	while (str_split[i])
	{
		if (!ft_is_float(str_split[i]))
		{
			ft_strarr_del(str_split);
			return (RT_FAILURE);
		}
		i++;
	}
	float3->x = ft_atof(str_split[0]);
	float3->y = ft_atof(str_split[1]);
	float3->z = ft_atof(str_split[2]);
	ft_strarr_del(str_split);
	return (RT_SUCCESS);
}

t_bool	ft_is_float(const char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '.' || !str[i])
		return (RT_FALSE);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1 || str[i + 1] == '\0')
				return (RT_FALSE);
		}
		else if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (RT_FALSE);
		i++;
	}
	return (RT_TRUE);
}
