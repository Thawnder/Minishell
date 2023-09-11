/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:10:12 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 12:19:46 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_inttest(int nb, char *format, int *idx)
{
	if (!(belongs_to('.', format, ft_strlen(format))
			&& nb == 0
			&& (ft_nbdet(format, ft_strlen(format)) == -42
				|| (*idx + get_int_length(nb)) == 0)))
		return (1);
	else if (ft_nbdet(format, ft_strlen(format)) == 0)
		return (1);
	return (0);
}

void	ft_loopfillint(int res, char *f, int *cmp, int *size)
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

void	ft_ressize_int(int res, char *f, int *idx, int *size)
{
	int	i;
	int	j;
	int	tmp;
	int	z;
	int	a;

	j = ft_fieldflaglen(f, &i);
	tmp = ft_preciflaglen(f, &z);
	a = ft_atoi(&f[i], j) - ft_max(get_int_length(res), ft_atoi(&f[z], tmp));
	if (!belongs_to('.', f, ft_strlen(f)))
		*size = get_int_length(res);
	else if (ft_nbdet(f, ft_strlen(f)) >= 0)
	{
		*size = ft_max(get_int_length(res), ft_atoi(&f[i], j)) - a;
		if (ft_atoi(&f[i], j) < get_int_length(res))
			*size += ft_max(get_int_length(res), ft_atoi(&f[z], tmp));
		*idx = ft_atoi(&f[z], tmp) - get_int_length(res);
	}
	else if (ft_nbdet(f, ft_strlen(f)) < 0)
	{
		*size = get_int_length(res);
		*idx = ft_atoi(&f[z], tmp) - get_int_length(res);
	}
	else
		*size = ft_atoi(&f[z], tmp) - ft_atoi(&f[i], j);
}

void	ft_testsign(int res, char *format, int *size)
{
	int	i;
	int	j;

	j = ft_fieldflaglen(format, &i);
	if (res < 0 && (ft_nbdet(format, ft_strlen(format)) == -1
			|| ft_nbdet(format, ft_strlen(format)) == 0)
		&& ft_atoi(&format[i], j) > get_int_length(res))
		*size += 1;
}

void	ft_flagitoa(int res, int *cmp, char *format, int *idx)
{
	int	i;
	int	j;
	int	size;
	int	tmp;
	int	z;

	j = ft_fieldflaglen(format, &i);
	tmp = ft_preciflaglen(format, &z);
	ft_ressize_int(res, format, idx, &size);
	ft_testsign(res, format, &size);
	if (belongs_to('-', format, i))
		ft_put_itoa(res, cmp, format, idx);
	if (res < 0 && !belongs_to('-', format, ft_strlen(format))
		&& belongs_to('0', format, i))
		ft_putchar('-', cmp);
	if (ft_nbdet(format, ft_strlen(format)) < 0
		|| (ft_nbdet(format, ft_strlen(format)) == 0
			&& ft_atoi(&format[i], j) > ft_atoi(&format[z], tmp)))
		ft_loopfillint(res, format, cmp, &size);
	if (res < 0 && !belongs_to('-', format, ft_strlen(format))
		&& !belongs_to('0', format, i))
		ft_putchar('-', cmp);
	if (!belongs_to('-', format, i))
		ft_put_itoa(res, cmp, format, idx);
}
