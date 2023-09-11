/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:35:53 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/09 15:33:15 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_size(int n)
{
	size_t		size;

	size = 0;
	if (n < 0 || n == 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	ft_append(char *res, int c)
{
	size_t	i;

	i = ft_strlen(res);
	res[i] = c;
	res[i + 1] = '\0';
}

static void	rec(char *res, unsigned int n)
{
	if (n >= 10)
	{
		rec(res, n / 10);
		ft_append(res, n % 10 + 48);
	}
	else
		ft_append(res, n + 48);
}

char	*ft_itoa(int n)
{
	char	*res;

	res = malloc(calc_size(n) + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		res[1] = '\0';
		n *= -1;
	}
	rec(res, (unsigned int)n);
	return (res);
}
