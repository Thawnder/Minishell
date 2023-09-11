/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:12:55 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/07 17:33:37 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		size = ft_strlen(s) - start;
	else
		size = len;
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size && s)
	{
		str[i] = ((char *)s)[i + start];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*free_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		size = ft_strlen(s) - start;
	else
		size = len;
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size && s)
	{
		str[i] = ((char *)s)[i + start];
		i++;
	}
	str[i] = 0;
	free(s);
	return (str);
}
