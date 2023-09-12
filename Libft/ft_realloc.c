/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:19:31 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/07 11:19:47 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *dest, int size)
{
	char	*tmp;

	tmp = malloc(size + 1);
	if (!tmp)
		return (NULL);
	if (dest && dest[0])
	{
		ft_memcpy(tmp, dest, ft_strlen(dest) + 1);
		free(dest);
	}
	return (tmp);
}
