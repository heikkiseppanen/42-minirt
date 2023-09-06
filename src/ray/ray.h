/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:12:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/28 14:02:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "scene/ecs.h"
# include "renderer/geometry.h"

# include <ft/math.h>

# define RAY_MIN 0.000001f
# define RAY_MAX 5000.0f

typedef struct s_ray
{
	t_float3	origin;
	t_float3	direction;
}	t_ray;

typedef struct s_hit
{
	t_id		entity;
	t_float3	position;
	t_float3	normal;
}	t_hit;

// Casts a given ray against given scene data.
// If the ray hits, returns true and stores collision info into result.
t_bool	ray_cast(const t_ray *r, const t_ecs *scene, t_hit *result);

float	ray_scene_intersect(
			const t_ray *self,
			const t_ecs *scene,
			t_id	*opt_entity_hit); 

float	ray_geometry_intersect(
			const t_ray *self,
			const t_geometry *geometry,
			const t_float3 *position);

float	ray_sphere_intersect(
			const t_ray *self,
			const t_sphere *sp,
			const t_float3 *pos);

float ray_plane_intersect(
    const t_ray *self,
    const t_plane *pl,
    const t_float3 *pos);

#endif
