/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:29:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 13:24:43 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_dollars(t_mini *mini, t_lists *tmp)
{
	int	i;
	int	quote;

	quote = -1;
	i = 0;
	if (!has_dollar(tmp->arg, 0, ft_strlen(tmp->arg)))
		return ;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == '\'' || tmp->arg[i] == '"')
			quote *= -1;
		if (quote == -1 && tmp->arg[i] == '$' && tmp->arg[i + 1]
			&& tmp->arg[i + 1] != ' ')
			tmp->arg = manage_dollars(mini, tmp->arg, i, ft_strlen(tmp->arg));
		else
			i++;
	}
}
