/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:32:19 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 11:30:50 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/io.h"

int	ft_putdec_u64_fd(unsigned long long nb, int fd)
{
	return (ft_put_u64_base_fd(nb, 10, "0123456789", fd));
}

int	ft_putdec_i64_fd(long long nb, int fd)
{
	return (ft_put_i64_base_fd(nb, 10, "0123456789", fd));
}

int	ft_putdec_u64(unsigned long long nb)
{
	return (ft_putdec_u64_fd(nb, STDOUT_FILENO));
}

int	ft_putdec_i64(long long nb)
{
	return (ft_putdec_i64_fd(nb, STDOUT_FILENO));
}
