/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:52:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/05 11:57:37 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

int	ft_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
