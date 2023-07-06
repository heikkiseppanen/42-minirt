/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:08:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/cstr.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = 0;
	srclen = ft_strlen(src);
	while (dstlen < dstsize && *dst)
	{
		dstlen++;
		dst++;
	}
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	dstsize -= (dstlen + 1);
	ft_memcpy(dst, src, dstsize);
	if (dstsize > srclen)
		dst[srclen] = '\0';
	else
		dst[dstsize] = '\0';
	return (dstlen + srclen);
}
