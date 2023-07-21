/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:15:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/21 10:04:15 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUF_H
# define BUF_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buf
{
	void	*data;
	size_t	stride;
	size_t	size;
	size_t	cap;
}			t_buf;

int		ft_buf_init(t_buf *arr, size_t size, size_t type_size);
void	ft_buf_del(t_buf *arr);

int		ft_buf_resize(t_buf *arr, size_t new_cap);
int		ft_buf_pushback(t_buf *arr, void *type_data, size_t count);

void	*ft_buf_get(const t_buf *buf, size_t i);

ssize_t	ft_buf_read(t_buf *arr, int fd, size_t bytes);

#endif
