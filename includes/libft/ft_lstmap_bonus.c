/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:04:24 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/23 14:24:09 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*new_node(t_list **new_lst, void **content, void (*del)(void *))
{
	t_list	*node;

	node = ft_lstnew((*content));
	if (!node)
	{
		free((*content));
		ft_lstclear(new_lst, del);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!(content))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		node = new_node(&new_lst, &content, del);
		if (node == NULL)
			return (NULL);
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}
