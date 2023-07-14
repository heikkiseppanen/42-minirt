/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:24:03 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/14 08:38:32 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

t_float2	ft_float2_rot(t_float2 l, float rad)
{
	const float	dcos = cosf(rad);
	const float	dsin = sinf(rad);
	t_float2	result;

	result.x = (l.x * dcos) - (l.y * dsin);
	result.y = (l.x * dsin) + (l.y * dcos);
	return (result);
}
