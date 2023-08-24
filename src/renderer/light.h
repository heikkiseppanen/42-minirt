/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:59:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/24 14:07:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "renderer/color.h"
# include "scene/ecs.h"

t_color	calculate_surface_light(
	const t_float3 *position,
	const t_float3 *normal,
	const t_ecs *scene);

#endif
