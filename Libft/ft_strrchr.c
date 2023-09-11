/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:06:42 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/06 12:37:43 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			flag = 1;
		i++;
	}
	if (c == 0)
		flag = 1;
	if (flag == 1)
	{
		while ((unsigned char)s[i] != (unsigned char)c)
			i--;
		return ((char *)&s[i]);
	}
	return (0);
}
