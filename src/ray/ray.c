/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:07:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/31 12:55:15 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray/ray.h"


#include <stdio.h>

static float	ray_entity_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id entity)
{
	t_geometry const	*geo = ecs_get_component(scene, entity, ECS_GEOMETRY);
	t_float3 const		*pos = ecs_get_component(scene, entity, ECS_POSITION);

	if (geo->type == GEO_SPHERE)
	{
		return (ray_sphere_intersect(self, &geo->data.sphere, pos));
	}

	if (geo->type == GEO_PLANE)
	{
		return (ray_plane_intersect(self, &geo->data.plane, pos));
	}
	if (geo->type == GEO_CYLINDER)
	{
		return (ray_cylinder_intersect(self, &geo->data.cylinder, pos));
	}
	return (0.0f);
}

float	ray_scene_intersect(
	const t_ray *self,
	const t_ecs *scene,
	t_id	*opt_entity_hit)
{
	const t_id	*it = scene->renderables.data;
	const t_id	*end = it + scene->renderables.size;
	float		depth;
	float		min_depth;

	min_depth = RAY_MAX;
	while (it != end)
	{
		depth = ray_entity_intersect(self, scene, *it);
		if (depth > RAY_MIN && depth < min_depth)
		{
			if (opt_entity_hit != NULL)
			{
				*opt_entity_hit = *it;
			}
			min_depth = depth;
		}
		++it;
	}
	if (min_depth == RAY_MAX)
	{
		return (0.0f);
	}
	return (min_depth);
}

float	ray_sphere_intersect(
	const t_ray *self,
	const t_sphere *sp,
	const t_float3 *pos)
{
	const t_float3	oc = ft_float3_sub(self->origin, *pos);
	const float		a = ft_float3_dot(self->direction, self->direction);
	const float		b = ft_float3_dot(oc, self->direction);
	const float		c = ft_float3_dot(oc, oc) - (sp->radius * sp->radius);
	float d;

	d = (b * b) - (a * c);
	if (d < 0)
	{
		return (0.0f);
	}
	d = sqrtf(d);
	return ((-b - d) / a);
}

float ray_plane_intersect(
    const t_ray *self,
    const t_plane *pl,
    const t_float3 *pos)
{
    float    denom;
    float    t;
    denom = ft_float3_dot(pl->normal, self->direction);
    if (denom > 1e-6)
    {
        t = ft_float3_dot(ft_float3_sub(*pos, self->origin), pl->normal) / denom;
        return (t);
    }
    return (0.0f);
}

float ray_cylinder_intersect(
    const t_ray *self,
    const t_cylinder *cl,
    const t_float3 *pos)
{
	double a;
	double b;
	double c;

    a = self->direction.x * self->direction.x + self->direction.y * self->direction.y;
    b = 2 * (self->direction.x * (self->origin.x - pos->x) + self->direction.y * (self->origin.y - pos->y));
    c = (self->origin.x - pos->x) * (self->origin.x - pos->x) + (self->origin.y - pos->y) * (self->origin.y - pos->y) - cl->radius * cl->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1;
    }
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    double z1 = self->origin.z + t1 * self->direction.z;
    double z2 = self->origin.z + t2 * self->direction.z;


	double t_min = -1;

    if ((z1 >= pos->z - cl->height / 2 && z1 <= pos->z + cl->height / 2)) {
        t_min =  t1;
    } else if ((z2 >= pos->z - cl->height / 2 && z2 <= pos->z + cl->height / 2)) {
        t_min = t2;
    }

	double t_cap1 = (pos->z - cl->height / 2 - self->origin.z) / self->direction.z;
    double t_cap2 = (pos->z + cl->height / 2 - self->origin.z) / self->direction.z;

	    if (t_cap1 >= 0)
		{
        double x_cap1 = self->origin.x + t_cap1 * self->direction.x - pos->x;
        double y_cap1 = self->origin.y + t_cap1 * self->direction.y - pos->y;
        double dist_cap1 = x_cap1 * x_cap1 + y_cap1 * y_cap1;

        if (dist_cap1 <= cl->radius * cl->radius && (t_min == -1 || t_cap1 < t_min)) {
            t_min = t_cap1;
        }
    }
    if (t_cap2 >= 0)
	{
        double x_cap2 = self->origin.x + t_cap2 * self->direction.x - pos->x;
        double y_cap2 = self->origin.y + t_cap2 * self->direction.y - pos->y;
        double dist_cap2 = x_cap2 * x_cap2 + y_cap2 * y_cap2;
        
        if (dist_cap2 <= cl->radius * cl->radius && (t_min == -1 || t_cap2 < t_min)) {
            t_min = t_cap2;
        }
    }
    return t_min;
}

void	calc_surface_normal(const t_ecs *scene, t_hit *out)
{
	t_geometry const	*geo = ecs_get_component(scene, out->entity, ECS_GEOMETRY);

	if (geo->type == GEO_PLANE)
	{
		out->normal = ft_float3_scalar(geo->data.plane.normal, -1);
	}
	if (geo->type == GEO_SPHERE)
	{
		out->normal = *(t_float3 *)ecs_get_component(scene, out->entity, ECS_POSITION);
		out->normal = ft_float3_sub(out->position, out->normal);
		out->normal = ft_float3_normalize(out->normal);
	}
}

t_bool	ray_cast(const t_ray *self, const t_ecs *scene, t_hit *out)
{
	const float depth = ray_scene_intersect(self, scene, &out->entity);
	
	if (!depth)
	{
		return (RT_FALSE);
	}
	out->position = ft_float3_scalar(self->direction, depth);
	out->position = ft_float3_add(self->origin, out->position);

	calc_surface_normal(scene, out);

	return (RT_TRUE);
}