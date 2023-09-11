/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:43:48 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/10 15:36:27 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*check(void *tmp, t_list **lst, void (*del)(void *))
{
	*lst = ft_lstnew(tmp);
	if (!lst)
	{
		del(tmp);
		return (NULL);
	}
	return (*lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newelt;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	newlst = check(f(lst->content), &newlst, del);
	if (!newlst)
		return (NULL);
	newelt = newlst;
	while (lst->next)
	{
		tmp = f(lst->next->content);
		newelt->next = ft_lstnew(tmp);
		if (!newelt->next)
		{
			ft_lstclear(&newlst, del);
			del(tmp);
			return (NULL);
		}
		newelt = newelt->next;
		lst = lst->next;
	}
	return (newlst);
}
