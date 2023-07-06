/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:13:06 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 11:35:45 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/list.h"

#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*it;
	t_list	*next;

	if (!lst || !del)
		return ;
	it = *lst;
	while (it)
	{
		next = it->next;
		ft_lstdelone(it, del);
		it = next;
	}
	*lst = NULL;
}
