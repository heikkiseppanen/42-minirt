/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:14:19 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 11:35:32 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/list.h"

#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*it;

	if (!f || !del || !lst)
		return (NULL);
	new = ft_lstnew(lst->content);
	if (!new)
		return (NULL);
	it = new;
	while (lst)
	{
		lst = lst->next;
		it->next = ft_lstnew(f(lst->content));
		if (!it->next)
		{
			ft_lstclear(&new, del);
			return (new);
		}
		it = it->next;
	}
	return (new);
}
