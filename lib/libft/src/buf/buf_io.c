/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:21:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/buf.h"

ssize_t	ft_buf_read(t_buf *buf, int fd, size_t bytes)
{
	size_t			byte_cap;
	size_t			byte_size;
	ssize_t			read_size;
	void			*dst;

	byte_size = buf->size * buf->stride;
	byte_cap = buf->cap * buf->stride;
	while (byte_size + bytes > byte_cap)
	{
		if (ft_buf_resize(buf, 2 * buf->cap))
		{
			byte_size = buf->size * buf->stride;
			byte_cap = buf->cap * buf->stride;
		}
		else
			return (-1);
	}
	dst = (unsigned char *)buf->data + byte_size;
	read_size = read(fd, dst, bytes);
	if (read_size > 0)
		buf->size += read_size;
	return (read_size);
}
