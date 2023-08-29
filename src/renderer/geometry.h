/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:18:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/28 14:05:45 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <ft/math.h>

typedef struct s_sphere
{
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_float3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_float3	normal;
	float		radius;
	float		height;
}	t_cylinder;

typedef enum e_geo_type
{
	GEO_SPHERE = 0,
	GEO_PLANE,
	GEO_CYLINDER,
}	t_geo_type;

typedef union e_geo_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_geo_data;

typedef struct s_geometry
{
	t_geo_type	type;
	t_geo_data	data;
}	t_geometry;

#endif
