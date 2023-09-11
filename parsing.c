/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:03:11 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 11:05:28 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_is_pipe(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->previous && tmp->is_pipe)
			tmp->previous->is_pipe = 1;
		tmp = tmp->previous;
	}
}

void	ft_amp_or(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		if (tmp->operator == OP_2AMP || tmp->operator == OP_2PIPE)
		{
			//if (ft_try_command())
		}
		tmp = tmp->next;
	}
}

void	ft_parse(t_mini *mini)
{
	add_is_pipe(mini);
	ft_amp_or(mini);
	/*
		TRY FONCTION AND ADD && AND || TRUE AND DELETE USELESS

		PRIORITY WITH ( )

		ADD NUM ARGS


		
	*/
	
}
