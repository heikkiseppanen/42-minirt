/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:40:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/06 10:16:57 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float2	ft_float2_normalize(t_float2 vector)
{
	const float	len = ft_float2_len(vector);

	vector.x /= len;
	vector.y /= len;
	return (vector);
}

float	ft_float2_dot(t_float2 l, t_float2 r)
{
	return ((l.x * r.x) + (l.y * r.y));
}

float	ft_float2_cross(t_float2 l, t_float2 r)
{
	return ((l.x * r.y) - (l.y * r.x));
}
