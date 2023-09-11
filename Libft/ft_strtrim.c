/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:44:12 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/09 15:36:14 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(set) == 0 || ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[j]) != 0)
		j--;
	res = malloc(j - i + 2);
	if (!res)
		return (NULL);
	k = 0;
	while (i <= j)
		res[k++] = s1[i++];
	res[k] = 0;
	return (res);
}
