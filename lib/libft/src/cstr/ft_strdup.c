/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:57:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/cstr.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s1) + 1;
	dup = malloc(size * sizeof(*dup));
	if (dup)
		ft_memcpy(dup, s1, size);
	return (dup);
}
