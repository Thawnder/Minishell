/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:29:07 by user              #+#    #+#             */
/*   Updated: 2023/10/11 14:16:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_need_space(char *str, char *old_str, int *i, int *y)
{
	if (old_str[*i - 1] == '"')
	{
		while (old_str[*i] && old_str[*i] != '"')
		{
			str[*y] = old_str[*i];
			*y += 1;
			*i += 1;
		}
		str[*y] = old_str[*i];
		*y += 1;
		*i += 1;
	}
	else if (old_str[*i - 1] == '\'')
	{
		while (old_str[*i] && old_str[*i] != '\'')
		{
			str[*y] = old_str[*i];
			*y += 1;
			*i += 1;
		}
		str[*y] = old_str[*i];
		*y += 1;
		*i += 1;
	}
}

int	ft_check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				return (-1);
		}
	}
	return (0);
}
