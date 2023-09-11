/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:35:16 by bpleutin          #+#    #+#             */
/*   Updated: 2023/03/23 12:23:16 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

# define FLAGSET "-0.# +*123456789"
# define CONVSET "cspdiuxX%"
# define HEXMIN "0123456789abcdef"
# define HEXMAJ "0123456789ABCDEF"

void	ft_put_itoa(int nb, int *cmp, char *format, int *idx);
void	ft_put_uitoa(unsigned int nb, int *cmp, char *format, int *idx);
void	ft_puthexmin(unsigned int nb, int *cmp, char *format, int *idx);
void	ft_puthexmaj(unsigned int nb, int *cmp, char *format, int *idx);
void	ft_puthexptr(unsigned long long nb, int *cmp, char *format, int *idx);
void	ft_putstr(char *str, int *cmp, char *format, int *idx);
void	ft_putchar(char c, int *cmp);
void	ft_charcat(char *dest, char src);
int		ft_convert(char *format, va_list set, char conv);
int		get_format_length(const char *str);
int		ft_printflag(const char *str, int *it, char *format);
int		ft_printf(const char *str, ...);
int		get_int_length(int nb);
int		get_uint_length(unsigned int nb);
int		get_hex_length(unsigned long long nb);
int		ft_preciflaglen(char *str, int *i);
int		ft_fieldflaglen(char *str, int *i);
int		ft_nbdet(char *format, int limit);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_hextest(unsigned int nb, char *format, int *idx);
int		ft_uinttest(unsigned int nb, char *format, int *idx);
void	ft_ressize_hex(unsigned int res, char *f, int *idx, int *size);
void	ft_ressize_uint(unsigned int res, char *f, int *idx, int *size);
void	ft_fill(char *format, int limit, int *cmp, int *it);
void	ft_loopfill(int res, char *f, int *cmp, int *size);
void	ft_loopfillint(int res, char *f, int *cmp, int *size);
void	ft_loopfillstr(char *res, char *f, int *cmp, int *size);
int		ft_sizecond(char *res, char *f, int field, int preci);
void	ft_ressize_str(char *res, char *f, int *idx, int *size);
void	ft_prefix(long int res, char *format, int *cmp, int maj);
void	ft_itoaloop(unsigned int res, int *cmp, int length);
void	ft_spaceplus(int nb, char *format, int *cmp);
int		ft_inttest(int nb, char *format, int *idx);
int		ft_uinttest(unsigned int nb, char *format, int *idx);
size_t	ft_strlen(const char *str);
int		ft_reslen(char *str, char *f);
int		puissance(int val, int p);
int		belongs_to(char c, char *set, int limit);
void	ft_bzero(void *s, size_t n);
void	*ft_libftcalloc(size_t nmemb, size_t size);
int		ft_atoi(char *str, int size);
void	ft_flagchar(char res, int *cmp, char *format);
void	ft_flagstr(char *res, int *cmp, char *format, int *idx);
void	ft_flaghexptr(unsigned long long res, int *cmp, char *format, int *idx);
void	ft_flagitoa(int res, int *cmp, char *format, int *idx);
void	ft_flaguitoa(unsigned int res, int *cmp, char *format, int *idx);
void	ft_flaghexmin(unsigned int res, int *cmp, char *format, int *idx);
void	ft_flaghexmaj(unsigned int res, int *cmp, char *format, int *idx);

#endif
