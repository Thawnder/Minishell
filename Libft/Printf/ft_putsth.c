/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:22:20 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/24 16:02:49 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_uitoa(unsigned int nb, int *cmp, char *format, int *idx)
{
	int				length;

	length = get_uint_length(nb);
	if (ft_uinttest(nb, format, idx))
	{
		while (*idx > 0)
		{
			ft_putchar('0', cmp);
			*idx -= 1;
		}
		ft_itoaloop(nb, cmp, length);
	}
}

void	ft_puthexmin(unsigned int nb, int *cmp, char *format, int *idx)
{
	char			tmp;

	if (ft_hextest(nb, format, idx))
	{
		while (*idx > 0)
		{
			ft_putchar('0', cmp);
			*idx -= 1;
		}
		if (nb < 16)
		{
			tmp = HEXMIN[nb];
			ft_putchar(tmp, cmp);
		}
		else
		{
			ft_puthexmin(nb / 16, cmp, format, idx);
			tmp = HEXMIN[nb % 16];
			ft_putchar(tmp, cmp);
		}
	}
}

void	ft_puthexmaj(unsigned int nb, int *cmp, char *format, int *idx)
{
	char			tmp;

	if (ft_hextest(nb, format, idx))
	{
		while (*idx > 0)
		{
			ft_putchar('0', cmp);
			*idx -= 1;
		}
		if (nb < 16)
		{
			tmp = HEXMAJ[nb];
			ft_putchar(tmp, cmp);
		}
		else
		{
			ft_puthexmaj(nb / 16, cmp, format, idx);
			tmp = HEXMAJ[nb % 16];
			ft_putchar(tmp, cmp);
		}
	}
}

void	ft_puthexptr(unsigned long long nb, int *cmp, char *format, int *idx)
{
	unsigned long long	res;
	char				tmp;

	if (!nb)
	{
		ft_putstr("(nil)", cmp, format, idx);
		return ;
	}
	if (*cmp == 0 || *idx == 1)
		ft_putstr("0x", cmp, format, idx);
	*idx = 0;
	res = nb;
	if (res < 16)
	{
		tmp = HEXMIN[res];
		ft_putchar(tmp, cmp);
	}
	else
	{
		ft_puthexptr(res / 16, cmp, format, idx);
		tmp = HEXMIN[res % 16];
		ft_putchar(tmp, cmp);
	}
}

void	ft_charcat(char *dest, char src)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest[i] = src;
	i++;
	dest[i] = '\0';
}
