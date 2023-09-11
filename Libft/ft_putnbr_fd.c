/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:17:15 by bpleutin          #+#    #+#             */
/*   Updated: 2023/02/09 13:24:36 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	res;
	char			tmp;

	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	res = n;
	if (res < 10)
	{
		tmp = res + 48;
		write(fd, &tmp, sizeof(char));
	}
	else
	{
		ft_putnbr_fd(res / 10, fd);
		tmp = res % 10 + 48;
		write(fd, &tmp, sizeof(char));
	}
}
