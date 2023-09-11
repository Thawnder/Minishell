/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:03 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/01 17:40:30 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

void	*ft_libftcalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	res;

	res = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (res / size != nmemb || res / nmemb != size)
		return (NULL);
	ptr = malloc(res);
	if (ptr)
		ft_bzero(ptr, res);
	return (ptr);
}

int	ft_atoi(char *str, int size)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9' && i < size)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}

int	ft_preciflaglen(char *str, int *i)
{
	int	j;

	j = 0;
	*i = 0;
	if (str[0])
	{
		while (str[*i])
			*i += 1;
		while (*i - 1 >= 0 && str[*i - 1] >= '0' && str[*i - 1] <= '9')
		{
			if (str[*i - 1] == '0'
				&& (*i - 1 == 0
					|| (j == 0 && str[*i - 2] == '.'
						&& str[*i - 3] >= '0' && str[*i - 3] <= '9')))
				return (j);
			j++;
			*i -= 1;
		}
	}
	return (j);
}

void	ft_flagchar(char res, int *cmp, char *format)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = ft_fieldflaglen(format, &i);
	k = 0;
	if (belongs_to('-', format, i))
		ft_putchar(res, cmp);
	while (k < ft_atoi(&format[i], j) - 1)
	{
		if (belongs_to('0', format, i))
			ft_putchar('0', cmp);
		else
			ft_putchar(' ', cmp);
		k++;
	}
	if (!belongs_to('-', format, i))
		ft_putchar(res, cmp);
}
