/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:51:54 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/14 11:27:25 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_option_echo(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != ' ')
		i++;
	if (str[++i] && str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] != 'n')
				return (0);
			i++;	
		}
		return (1);
	}
	return (0);
}