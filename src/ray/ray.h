/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:12:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/12 09:56:10 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "scene/ecs.h"
# include "renderer/geometry.h"

# include <ft/math.h>

# define EPSILON 1e-4
# define RAY_MIN 1e-4
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

t_float3	ray_at(const t_ray *self, float d);

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
			const t_float3 *pos,
			const float radius);

float	ray_plane_intersect(
			const t_ray *self,
			const t_float3 *pos,
			const t_float3 *normal);

float	ray_cylinder_intersect(
			const t_ray *self,
			const t_float3 *pos,
			const t_cylinder *cl);

#endif
