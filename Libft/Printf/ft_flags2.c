/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:37:34 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 12:18:32 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_fieldflaglen(char *str, int *i)
{
	int	j;

	j = 0;
	*i = 0;
	if (str[0])
	{
		while (str[*i] && str[*i] != '.')
			*i += 1;
		while (*i - 1 >= 0 && str[*i - 1] >= '0' && str[*i - 1] <= '9')
		{
			if (str[*i - 1] == '0' && *i - 1 == 0
				&& !((str[*i] >= '0' && str[*i] <= '9')
					&& belongs_to('.', str, ft_strlen(str))))
				return (j);
			j++;
			*i -= 1;
		}
	}
	return (j);
}

int	ft_nbdet(char *format, int limit)
{
	int	j;

	j = 0;
	if (belongs_to('.', format, limit))
	{
		if (ft_preciflaglen(format, &j) != 0
			&& ft_fieldflaglen(format, &j) != 0)
			return (0);
		if (ft_preciflaglen(format, &j) != 0)
			return (1);
		if (ft_fieldflaglen(format, &j) != 0)
			return (-1);
	}
	else
		if (ft_fieldflaglen(format, &j) != 0)
			return (-1);
	return (-42);
}

void	ft_fill(char *format, int limit, int *cmp, int *it)
{
	if (belongs_to('0', format, limit))
		ft_putchar('0', cmp);
	else
		ft_putchar(' ', cmp);
	*it += 1;
}

void	ft_flagstr(char *res, int *cmp, char *format, int *idx)
{
	int	size;

	ft_ressize_str(res, format, idx, &size);
	if (belongs_to('-', format, ft_strlen(format)))
		ft_putstr(res, cmp, format, idx);
	if (ft_nbdet(format, ft_strlen(format)) == -1
		|| (ft_nbdet(format, ft_strlen(format)) == 0))
		ft_loopfillstr(res, format, cmp, &size);
	if (!belongs_to('-', format, ft_strlen(format)))
		ft_putstr(res, cmp, format, idx);
}
