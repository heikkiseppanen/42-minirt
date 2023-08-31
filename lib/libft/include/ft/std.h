/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:27:04 by hseppane          #+#    #+#             */
/*   Updated: 2023/08/31 09:32:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_H
# define STD_H

# include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);

float	ft_atof(const char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif
