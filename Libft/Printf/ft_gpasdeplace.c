/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpasdeplace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:14:12 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/03 17:20:06 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_loopfillstr(char *res, char *f, int *cmp, int *size)
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
		if (ft_strlen(res) > 0)
			ft_fill(f, i, cmp, size);
	}
	else
	{
		while (ft_nbdet(f, ft_strlen(f)) <= 0 && *size < ft_atoi(&f[i], j))
			ft_fill(f, i, cmp, size);
	}
}

int	ft_sizecond(char *res, char *f, int field, int preci)
{
	int	a;
	int	b;
	int	size;

	size = 0;
	a = field - ft_min(ft_reslen(res, f), preci);
	b = preci - ft_min(ft_reslen(res, f), field);
	if (preci <= field)
		size = field - a;
	else
		size = preci - b;
	return (size);
}

void	ft_ressize_str(char *res, char *f, int *idx, int *size)
{
	int	i;
	int	j;
	int	tmp;
	int	z;

	j = ft_fieldflaglen(f, &i);
	tmp = ft_preciflaglen(f, &z);
	if (!belongs_to('.', f, ft_strlen(f)))
		*size = ft_reslen(res, f);
	else if (ft_nbdet(f, ft_strlen(f)) >= 0)
	{
		*size = ft_sizecond(res, f, ft_atoi(&f[i], j), ft_atoi(&f[z], tmp));
		*idx = ft_atoi(&f[z], tmp) - ft_reslen(res, f);
	}
	else if (ft_nbdet(f, ft_strlen(f)) == -1)
	{
		*size = ft_atoi(&f[z], tmp);
		*idx = ft_atoi(&f[z], tmp) - ft_reslen(res, f);
	}
	else
		*size = ft_atoi(&f[z], tmp) - ft_atoi(&f[i], j);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_reslen(char *str, char *f)
{
	int	tmp;
	int	z;
	int	len;

	z = 0;
	len = 0;
	tmp = ft_preciflaglen(f, &z);
	if (!str && (!belongs_to('.', f, ft_strlen(f))
			|| (ft_nbdet(f, ft_strlen(f)) != 42
				&& (ft_nbdet(f, ft_strlen(f)) >= 0
					&& ft_atoi(&f[z], tmp) >= 6))))
		len = 6;
	else
		len = ft_strlen(str);
	return (len);
}
