/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/04 11:42:16 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer/ray.h"

//static float	min_positivef(float a, float b)
//{
//	(void)a;
//	(void)b;
//	return 0;
//}

t_bool	ray_hit(t_ray *r, t_geometry *geo, t_float3 *pos, t_hit *result)
{
	(void)r;
	(void)geo;
	(void)pos;
	(void)result;
	return RT_TRUE;
}

float	ray_sphere_intersect(const t_ray *ray, t_float3 center, float radius)
{
	const t_float3 oc = ft_float3_sub(ray->origin, center);
	const float a = ft_float3_dot(ray->direction, ray->direction);
	const float b = ft_float3_dot(oc, ray->direction);
	const float c = ft_float3_dot(oc, oc) - (radius * radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return RT_FALSE;
	}
	d = sqrtf(d);
	return ((-b - d) / a);
	//return (min_positivef((-b - d) / a, (-b + d) / a));
}
