/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:09 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 12:19:22 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_uint_length(unsigned int nb)
{
	int	cpt;

	cpt = 1;
	nb = nb / 10;
	while (nb != 0)
	{
		nb = nb / 10;
		cpt++;
	}
	return (cpt);
}

void	ft_itoaloop(unsigned int res, int *cmp, int length)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < length)
	{
		if (i == length - 1)
			tmp = res % 10 + 48;
		else
			tmp = (res / puissance(10, length - i - 1)) % 10 + 48;
		ft_putchar(tmp, cmp);
		i++;
	}
}

int	ft_uinttest(unsigned int nb, char *format, int *idx)
{
	if (!(belongs_to('.', format, ft_strlen(format))
			&& nb == 0
			&& (ft_nbdet(format, ft_strlen(format)) == -42
				|| (*idx + get_uint_length(nb)) == 0)))
		return (1);
	else if (ft_nbdet(format, ft_strlen(format)) == 0)
		return (1);
	return (0);
}

void	ft_ressize_uint(unsigned int res, char *f, int *idx, int *size)
{
	int	i;
	int	j;
	int	tmp;
	int	z;
	int	a;

	j = ft_fieldflaglen(f, &i);
	tmp = ft_preciflaglen(f, &z);
	a = ft_atoi(&f[i], j) - ft_max(get_uint_length(res), ft_atoi(&f[z], tmp));
	if (!belongs_to('.', f, ft_strlen(f)))
		*size = get_uint_length(res);
	else if (ft_nbdet(f, ft_strlen(f)) >= 0)
	{
		*size = ft_max(get_uint_length(res), ft_atoi(&f[i], j)) - a;
		if (ft_atoi(&f[i], j) < get_uint_length(res))
			*size += ft_max(get_uint_length(res), ft_atoi(&f[z], tmp));
		*idx = ft_atoi(&f[z], tmp) - get_uint_length(res);
	}
	else if (ft_nbdet(f, ft_strlen(f)) < 0)
	{
		*size = get_uint_length(res);
		*idx = ft_atoi(&f[z], tmp) - get_uint_length(res);
	}
	else
		*size = ft_atoi(&f[z], tmp) - ft_atoi(&f[i], j);
}

void	ft_flaguitoa(unsigned int res, int *cmp, char *format, int *idx)
{
	int	i;
	int	j;
	int	size;
	int	tmp;
	int	z;

	j = ft_fieldflaglen(format, &i);
	tmp = ft_preciflaglen(format, &z);
	ft_ressize_uint(res, format, idx, &size);
	if (belongs_to('-', format, i))
		ft_put_uitoa(res, cmp, format, idx);
	if (ft_nbdet(format, ft_strlen(format)) == -1
		|| (ft_nbdet(format, ft_strlen(format)) == 0
			&& ft_atoi(&format[i], j) > ft_atoi(&format[z], tmp)))
		ft_loopfill(res, format, cmp, &size);
	if (!belongs_to('-', format, i))
		ft_put_uitoa(res, cmp, format, idx);
}
