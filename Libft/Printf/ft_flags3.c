/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:21:43 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/03 11:20:41 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flaghexptr(unsigned long long res, int *cmp, char *format, int *idx)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = ft_fieldflaglen(format, &i);
	if (res)
		size = get_hex_length(res) + 2;
	else
		size = 5;
	if (belongs_to('-', format, i))
		ft_puthexptr(res, cmp, format, idx);
	while (size < ft_atoi(&format[i], j))
	{
		ft_fill(format, i, cmp, &size);
		*idx = 1;
	}
	if (!belongs_to('-', format, i))
		ft_puthexptr(res, cmp, format, idx);
}

int	ft_hextest(unsigned int nb, char *format, int *idx)
{
	if (!(belongs_to('.', format, ft_strlen(format))
			&& nb == 0
			&& (ft_nbdet(format, ft_strlen(format)) == -42
				|| (*idx + get_hex_length(nb)) == 0)))
		return (1);
	else if (ft_nbdet(format, ft_strlen(format)) == 0)
		return (1);
	return (0);
}

void	ft_ressize_hex(unsigned int res, char *f, int *idx, int *size)
{
	int	i;
	int	j;
	int	tmp;
	int	z;
	int	a;

	j = ft_fieldflaglen(f, &i);
	tmp = ft_preciflaglen(f, &z);
	a = ft_atoi(&f[i], j) - ft_max(get_hex_length(res), ft_atoi(&f[z], tmp));
	if (!belongs_to('.', f, ft_strlen(f)))
		*size = get_hex_length(res);
	else if (ft_nbdet(f, ft_strlen(f)) >= 0)
	{
		*size = ft_max(get_hex_length(res), ft_atoi(&f[i], j)) - a;
		if (ft_atoi(&f[i], j) < get_hex_length(res))
			*size += ft_max(get_hex_length(res), ft_atoi(&f[z], tmp));
		*idx = ft_atoi(&f[z], tmp) - get_hex_length(res);
	}
	else if (ft_nbdet(f, ft_strlen(f)) == -1)
	{
		*size = get_hex_length(res);
		*idx = ft_atoi(&f[z], tmp) - get_hex_length(res);
	}
	else
		*size = ft_atoi(&f[z], tmp) - ft_atoi(&f[i], j);
}

void	ft_flaghexmin(unsigned int res, int *cmp, char *format, int *idx)
{
	int	i;
	int	j;
	int	size;
	int	tmp;
	int	z;

	j = ft_fieldflaglen(format, &i);
	tmp = ft_preciflaglen(format, &z);
	ft_ressize_hex(res, format, idx, &size);
	if (belongs_to('-', format, i))
	{
		ft_prefix((long int)res, format, cmp, 0);
		ft_puthexmin(res, cmp, format, idx);
	}
	if (ft_nbdet(format, ft_strlen(format)) == -1
		|| (ft_nbdet(format, ft_strlen(format)) == 0
			&& ft_atoi(&format[i], j) > ft_atoi(&format[z], tmp)))
		ft_loopfill((int)res, format, cmp, &size);
	if (!belongs_to('-', format, i))
	{
		ft_prefix((long int)res, format, cmp, 0);
		ft_puthexmin(res, cmp, format, idx);
	}
}

void	ft_flaghexmaj(unsigned int res, int *cmp, char *format, int *idx)
{
	int	i;
	int	j;
	int	size;
	int	tmp;
	int	z;

	j = ft_fieldflaglen(format, &i);
	tmp = ft_preciflaglen(format, &z);
	ft_ressize_hex(res, format, idx, &size);
	if (belongs_to('-', format, i))
	{
		ft_prefix((long int)res, format, cmp, 1);
		ft_puthexmaj(res, cmp, format, idx);
	}
	if (ft_nbdet(format, ft_strlen(format)) == -1
		|| (ft_nbdet(format, ft_strlen(format)) == 0
			&& ft_atoi(&format[i], j) > ft_atoi(&format[z], tmp)))
		ft_loopfill((int)res, format, cmp, &size);
	if (!belongs_to('-', format, i))
	{
		ft_prefix((long int)res, format, cmp, 1);
		ft_puthexmaj(res, cmp, format, idx);
	}
}
