/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:53:59 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 11:31:11 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <stdio.h>
# include <unistd.h>

char	*get_next_line(int fd);

int		ft_fprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);

int		ft_put_u64_base_fd(unsigned long long nb, int base, char *set, int fd);
int		ft_put_i64_base_fd(long long nb, int base, char *set, int fd);

int		ft_puthex_upper_u64_fd(unsigned long long nb, int fd);
int		ft_puthex_upper_u64(unsigned long long nb);
int		ft_puthex_lower_u64_fd(unsigned long long nb, int fd);
int		ft_puthex_lower_u64(unsigned long long nb);

int		ft_putdec_u64_fd(unsigned long long nb, int fd);
int		ft_putdec_u64(unsigned long long nb);
int		ft_putdec_i64_fd(long long nb, int fd);
int		ft_putdec_i64(long long nb);

int		ft_putptr_fd(void *ptr, int fd);
int		ft_putptr(void *ptr);

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(const char *c, int fd);
int		ft_putendl_fd(const char *c, int fd);
int		ft_putnbr_fd(int n, int fd);

#endif
