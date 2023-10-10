/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:29:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/10 18:25:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_quotes(char *str, char c, int i)
{
	if (str[i] == c)
	{
		i++;
		while (str[i] != c)
			i++;
		i++;
	}
	return (i);
}

void	find_dollars(t_mini *mini, t_lists *tmp)
{
	int		i;
	int		quote;
	char	*old;

	quote = -1;
	i = 0;
	if (!has_dollar(tmp->arg, 0, ft_strlen(tmp->arg)))
		return ;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == '\'')
			i = next_quotes(tmp->arg, '\'', i);
		if (tmp->arg[i] == '"')
			i = next_quotes(tmp->arg, '"', i);
		if (quote == -1 && tmp->arg[i] && tmp->arg[i] == '$' && tmp->arg[i + 1]
			&& tmp->arg[i + 1] != ' ')
		{
			old = tmp->arg;
			tmp->arg = manage_dollars(mini, tmp->arg, i, ft_strlen(tmp->arg));
			free(old);
		}
		else
			i++;
	}
}
