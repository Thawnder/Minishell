/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:49:04 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/04 13:28:13 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_size(char const *s, char c)
{
	size_t	i;
	size_t	last;
	size_t	res;

	i = 0;
	last = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i - last >= 1)
				res++;
			last = i + 1;
		}
		i++;
	}
	if (i - last >= 1)
		res++;
	return (res);
}

static char	*ft_strndup2(const char *src, size_t n)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * n);
	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	init(size_t *i, size_t *last, size_t *k)
{
	*i = 0;
	*k = -1;
	*last = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	last;
	size_t	k;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (calc_size(s, c) + 1));
	if (!res)
		return (NULL);
	init(&i, &last, &k);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i - last >= 1)
				res[++k] = ft_strndup2(&s[last], i - last + 1);
			last = i + 1;
		}
		i++;
	}
	if (i - last >= 1)
		res[++k] = ft_strndup2(&s[last], i - last + 1);
	res[++k] = 0;
	return (res);
}

char	**ft_split_free(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	last;
	size_t	k;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (calc_size(s, c) + 1));
	if (!res)
		return (NULL);
	init(&i, &last, &k);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i - last >= 1)
				res[++k] = ft_strndup2(&s[last], i - last + 1);
			last = i + 1;
		}
		i++;
	}
	if (i - last >= 1)
		res[++k] = ft_strndup2(&s[last], i - last + 1);
	res[++k] = 0;
	return (free((char *)s), res);
}
