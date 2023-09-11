/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:14:50 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/10 10:37:58 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elt;

	if (lst && del)
	{
		while (*lst)
		{
			elt = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = elt;
		}
	}
}
