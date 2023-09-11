/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:33:09 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/09 10:48:35 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_count;

int	belongs_to(char c, char *set, int limit)
{
	int	i;

	i = 0;
	while (set[i] && i < limit)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_convert(char *format, va_list set, char conv)
{
	int	cmp;
	int	idx;

	cmp = 0;
	idx = 0;
	if (conv == 'c')
		ft_flagchar((char)va_arg(set, int), &cmp, format);
	else if (conv == 's')
		ft_flagstr(va_arg(set, char *), &cmp, format, &idx);
	else if (conv == 'p')
		ft_flaghexptr(va_arg(set, unsigned long long), &cmp, format, &idx);
	else if (conv == 'd' || conv == 'i')
		ft_flagitoa(va_arg(set, int), &cmp, format, &idx);
	else if (conv == 'u')
		ft_flaguitoa(va_arg(set, unsigned int), &cmp, format, &idx);
	else if (conv == 'x')
		ft_flaghexmin(va_arg(set, unsigned int), &cmp, format, &idx);
	else if (conv == 'X')
		ft_flaghexmaj(va_arg(set, unsigned int), &cmp, format, &idx);
	else if (conv == '%')
		ft_putchar('%', &cmp);
	free(format);
	return (cmp);
}

int	get_format_length(const char *str)
{
	int	i;

	i = 0;
	while (belongs_to(str[i], FLAGSET, ft_strlen(FLAGSET)))
		i++;
	if (belongs_to(str[i], CONVSET, ft_strlen(CONVSET)))
		i++;
	else
	{
		write(1, "Wrong format\n", 13);
		return (0);
	}
	return (i);
}

int	ft_printflag(const char *str, int *it, char *format)
{
	int		i;

	i = 0;
	while (belongs_to(str[i], FLAGSET, ft_strlen(FLAGSET)))
	{
		ft_charcat(format, str[i]);
		i++;
	}
	*it += i + 1;
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	set;
	char	*format;

	if (!str)
		return (0);
	i = 0;
	g_count = 0;
	va_start(set, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!get_format_length(&str[i + 1]))
				return (-1);
			format = ft_libftcalloc(get_format_length(&str[i + 1]), 1);
			ft_printflag(&str[i + 1], &i, format);
			g_count += ft_convert(format, set, str[i]);
		}
		else
			g_count += write(1, &str[i], 1);
		i++;
	}
	va_end(set);
	return (g_count);
}
