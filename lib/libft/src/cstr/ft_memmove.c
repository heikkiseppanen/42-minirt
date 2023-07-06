/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:24:30 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/cstr.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char			*dp;
	const unsigned char		*sp;

	if (dst == src || (!dst && !src))
		return (dst);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	dp = (unsigned char *)dst + (n - 1);
	sp = (const unsigned char *)src + (n - 1);
	while (n--)
		*dp-- = *sp--;
	return (dst);
}
