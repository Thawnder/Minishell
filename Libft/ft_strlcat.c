/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:35:05 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/06 14:57:09 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	if (size == 0 && (!dst || !src))
		return (0);
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	if (dlen >= size)
		return (size + slen);
	if (size > 0)
	{
		while (i < size - dlen - 1 && src[i] != '\0')
		{
			dst[i + dlen] = src[i];
			i++;
		}
		dst[i + dlen] = '\0';
	}
	return (slen + dlen);
}
