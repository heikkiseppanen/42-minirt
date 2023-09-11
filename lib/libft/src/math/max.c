/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:03:49 by hseppane          #+#    #+#             */
/*   Updated: 2023/09/05 11:56:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math.h"

int	ft_maxi(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
