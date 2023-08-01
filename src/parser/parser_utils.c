#include "parser/parser.h"
#include <ft/cstr.h>
#include <ft/std.h>
#include <stdio.h>

int		array_2d_length(char **array_2d)
{
	int	i;

	i = 0;
	while (array_2d[i])
	{
		i++;
	}
	return (i);
}

int	ft_free_array(char **arr)
{
	int	i;
	i = 0;

	while (arr && *arr != NULL)
	{
		free(*arr++);
		i++;
	}
	free(arr - i);
	return (0);
}

t_err	string_to_float3(const char *str, t_float3 *float3)
{
	int		i;
	char	**str_split;

	i = 0;
	str_split = ft_split(str, ',');
	if (!str_split || array_2d_length(str_split) != 3)
		return (RT_FAILURE + ft_free_array(str_split));
	while (str_split[i])
	{
		if (!ft_is_float(str_split[i]))
			return (RT_FAILURE + ft_free_array(str_split));
		i++;
	}
	float3->x = ft_atof(str_split[0]);
	float3->y = ft_atof(str_split[1]);
	float3->z = ft_atof(str_split[2]);
	ft_free_array(str_split);
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
	if (str[i] == '.')
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1 || str[i + 1] == '\0')
				return (0);
		}
		else if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
