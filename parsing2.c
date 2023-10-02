/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/02 15:24:10 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_mini *mini, t_lists *tmp, int pos)
{
	if (pipe(mini->old_fd) < 0)
		return ;
	if (pos == 0)
	{
		dup2(mini->old_fd[1], 1);
		ft_fork(mini, tmp->arg);
		close(mini->old_fd[1]);
	}
	else if (pos == 1)
	{
		dup2(mini->new_fd[0], 0);
		dup2(mini->old_fd[1], 1);
		ft_fork(mini, tmp->arg);
		close(mini->new_fd[0]);
		close(mini->old_fd[1]);
	}
	else
	{
		dup2(mini->old_fd[0], 0);
		ft_fork(mini, tmp->arg);
	}
	mini->new_fd[0] = mini->old_fd[0];
	mini->new_fd[1] = mini->old_fd[1];
}

t_lists	*ft_pipe(t_mini *mini, t_lists *tmp)
{
	while (tmp && (tmp->operator == OP_PIPE
		|| (tmp->previous && tmp->previous->operator == OP_PIPE)))
	{
		if (tmp->previous && tmp->previous->operator != OP_PIPE)
			child(mini, tmp, 0);
		else if (tmp->next && tmp->next->operator == OP_PIPE)
			child(mini, tmp, 1);
		else if (!tmp->next || (tmp->next && tmp->next->operator != OP_PIPE))
			child(mini, tmp, 2);
		tmp = tmp->next;
	}
	return (tmp);
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	if (tmp->operator == OP_PIPE)
		return (ft_pipe(mini, tmp));
	// else if (tmp->operator == OP_SUP || tmp->operator == OP_2SUP)
	// 	return (from_to(mini, tmp), tmp->next);
	// else
	// 	return (to_from(mini, tmp));
	
	
	return (tmp);
}
