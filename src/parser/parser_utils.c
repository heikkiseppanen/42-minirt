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

t_err	parse_error(__attribute__ ((unused)) char **tokens)
{
	printf("Line error\n");
	return (RT_FAILURE);
}

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

int	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

t_err	string_to_float3(const char *str, t_float3 *float3)
{
	int		i;
	char	**str_split;

	i = 0;
	str_split = ft_split(str, ',');
	if (!str_split || array_2d_length(str_split) != 3)
		return (RT_FAILURE + free_array(str_split));
	while (str_split[i])
	{
		if (!ft_is_float(str_split[i]))
			return (RT_FAILURE + free_array(str_split));
		i++;
	}
	float3->x = ft_atof(str_split[0]);
	float3->y = ft_atof(str_split[1]);
	float3->z = ft_atof(str_split[2]);
	free_array(str_split);
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
