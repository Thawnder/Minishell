/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:15:49 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/01 17:18:18 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_hex_length(unsigned long long nb)
{
	int	cpt;

	cpt = 1;
	nb = nb / 16;
	while (nb != 0)
	{
		nb = nb / 16;
		cpt++;
	}
	return (cpt);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_spaceplus(int nb, char *format, int *cmp)
{
	if (nb >= 0 && belongs_to(' ', format, ft_strlen(format)))
		ft_putchar(' ', cmp);
	if (nb >= 0 && belongs_to('+', format, ft_strlen(format)))
		ft_putchar('+', cmp);
}

void	ft_loopfill(int res, char *f, int *cmp, int *size)
{
	int	i;
	int	j;
	int	z;
	int	tmp;

	j = ft_fieldflaglen(f, &i);
	tmp = ft_preciflaglen(f, &z);
	if (belongs_to('.', f, ft_strlen(f)) && ft_nbdet(f, ft_strlen(f)) == -42)
	{
		while (ft_nbdet(f, ft_strlen(f)) <= 0 && *size < ft_atoi(&f[i], j)
			&& *cmp < ft_atoi(&f[z], tmp))
			ft_fill(f, i, cmp, size);
		if (res > 0)
			ft_fill(f, i, cmp, size);
	}
	else
	{
		while (ft_nbdet(f, ft_strlen(f)) <= 0 && *size < ft_atoi(&f[i], j))
			ft_fill(f, i, cmp, size);
		if (belongs_to('.', f, ft_strlen(f))
			&& ft_nbdet(f, ft_strlen(f)) < 0 && res == 0)
			ft_fill(f, i, cmp, size);
	}
}

void	ft_prefix(long int res, char *format, int *cmp, int maj)
{
	if (res != 0 && belongs_to('#', format, ft_strlen(format)))
	{
		ft_putchar('0', cmp);
		if (!maj)
			ft_putchar('x', cmp);
		else
			ft_putchar('X', cmp);
	}
}
