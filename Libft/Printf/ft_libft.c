/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:15:35 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/05 11:08:02 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *cmp)
{
	write(1, &c, sizeof(char));
	*cmp += 1;
}

void	ft_putstr(char *str, int *cmp, char *f, int *idx)
{
	int	i;
	int	tmp;

	*idx = 0;
	i = 0;
	tmp = ft_preciflaglen(f, idx);
	if (!str && (!belongs_to('.', f, ft_strlen(f))
			|| (ft_nbdet(f, ft_strlen(f)) != 42
				&& (ft_nbdet(f, ft_strlen(f)) >= 0
					&& ft_atoi(&f[*idx], tmp) >= 6))))
	{
		write(1, "(null)", 6);
		*cmp += 6;
	}
	else if (str)
	{
		while (str[i])
		{
			if (!f[0] || !belongs_to('.', f, ft_strlen(f))
				|| (ft_nbdet(f, ft_strlen(f)) >= 0
					&& i < ft_atoi(&f[*idx], tmp)))
				ft_putchar(str[i], cmp);
			i++;
		}
	}
}

int	get_int_length(int nb)
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

int	puissance(int val, int p)
{
	int	res;

	res = 1;
	while (p != 0)
	{
		res *= val;
		p--;
	}
	return (res);
}

void	ft_put_itoa(int nb, int *cmp, char *format, int *idx)
{
	unsigned int	res;
	int				length;

	ft_prefix((long int)nb, format, cmp, 1);
	if (ft_inttest(nb, format, idx))
	{
		if (nb < 0)
		{
			res = -(nb);
			if (belongs_to('-', format, ft_strlen(format)))
				ft_putchar('-', cmp);
		}
		else
			res = nb;
		while (*idx > 0)
		{
			ft_putchar('0', cmp);
			*idx -= 1;
		}
		length = get_int_length(res);
		ft_spaceplus(nb, format, cmp);
		ft_itoaloop(res, cmp, length);
	}
}
