/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:00:15 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/cstr.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*it;
	unsigned char	ch;

	it = (unsigned char *)b;
	ch = (unsigned char)c;
	while (len--)
	{
		*it = ch;
		it++;
	}
	return (b);
}
