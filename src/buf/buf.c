/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:10:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/19 12:57:54 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/buf.h"

#include "ft/cstr.h"

int	ft_buf_init(t_buf *buf, size_t size, size_t type_size)
{
	if (!buf || !size || !type_size)
		return (0);
	*buf = (t_buf){};
	buf->data = malloc(size * type_size);
	if (!buf->data)
		return (0);
	buf->stride = type_size;
	buf->cap = size;
	ft_bzero(buf->data, buf->cap * buf->stride);
	return (1);
}

void	ft_buf_del(t_buf *buf)
{
	if (buf->data)
		free(buf->data);
	*buf = (t_buf){};
}

int	ft_buf_resize(t_buf *buf, size_t new_cap)
{
	unsigned char	*new_data;

	if (!buf || !buf->data)
		return (0);
	if (new_cap == buf->cap)
		return (1);
	new_data = malloc(new_cap * buf->stride);
	if (!new_data)
		return (0);
	if (new_cap < buf->size)
	{
		ft_memcpy(new_data, buf->data, new_cap * buf->stride);
		buf->size = new_cap;
	}
	else
	{
		ft_memcpy(new_data, buf->data, buf->size * buf->stride);
	}
	free(buf->data);
	buf->data = new_data;
	buf->cap = new_cap;
	return (1);
}

int	ft_buf_pushback(t_buf *buf, void *type_data, size_t count)
{
	void	*dst;

	while (buf->size + count > buf->cap)
	{
		if (!ft_buf_resize(buf, 2 * buf->cap))
			return (0);
	}
	dst = (unsigned char *)buf->data + (buf->size * buf->stride);
	ft_memcpy(dst, type_data, count * buf->stride);
	buf->size += count;
	return (1);
}

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
