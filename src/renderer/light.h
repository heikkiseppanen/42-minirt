/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:59:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/14 13:29:38 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "renderer/color.h"
# include "scene/ecs.h"

typedef struct s_light
{
	float		attenuation;
	t_float3	color;
}	t_light;

t_color	calculate_surface_light(
			const t_float3 *position,
			const t_float3 *normal,
			const t_ecs *scene);

#endif
