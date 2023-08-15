/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:12:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/28 13:51:10 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "scene/ecs.h"

# include <ft/math.h>

typedef struct s_ray
{
	t_float3	origin;
	t_float3 	direction;
}	t_ray;

typedef struct s_hit
{
	float		depth;
	t_float3 	position;
	t_float3 	normal;
}	t_hit;

// Casts a given ray against given scene data.
// If the ray hits, returns true and stores collision info into result.
t_bool	ray_hit(t_ray *r, t_geometry *geo, t_float3 *pos, t_hit *result);

float	ray_sphere_intersect(const t_ray *ray, t_float3 center, float radius);

#endif
