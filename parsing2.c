/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/04 13:56:50 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_mini *mini, t_lists *tmp)
{
	if (check_builtin(tmp->arg, "exit") == 0
		|| check_builtin(tmp->arg, "echo") == 0
		|| check_builtin(tmp->arg, "cd") == 0
		|| check_builtin(tmp->arg, "pwd") == 0
		|| check_builtin(tmp->arg, "export") == 0
		|| check_builtin(tmp->arg, "unset") == 0
		|| check_builtin(tmp->arg, "env") == 0)
		ft_other_command(mini, tmp);
	return (1);
}

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
		child_between_pipe(mini, tmp);
	else
	{
		dup2(mini->new_fd[0], 0);
		dup2(mini->saved_stdout, 1);
		ft_fork(mini, tmp->arg);
		close(mini->new_fd[0]);
		dup2(mini->saved_stdin, 0);
	}
	mini->new_fd[0] = mini->old_fd[0];
	mini->new_fd[1] = mini->old_fd[1];
}

t_lists	*ft_pipe(t_mini *mini, t_lists *tmp)
{
	while (tmp && (tmp->operator == OP_PIPE
			|| (tmp->previous && tmp->previous->operator == OP_PIPE)))
	{
		if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
			|| !ft_is_builtin(mini, tmp))
		{
			dup2(mini->saved_stdin, 0);
			dup2(mini->saved_stdout, 1);
			if ((ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
					&& tmp->next && tmp->operator != OP_PIPE)
				return (tmp->next->prev_amp = AMP_FALSE
					, tmp->next->prev_or = OR_FALSE, tmp);
			else if (tmp->operator != OP_PIPE)
				return (tmp);
			dup2(STDIN_FILENO, 0);
			dup2(STDOUT_FILENO, 1);
			tmp = tmp->next;	
			continue;
		}
		if (!tmp->previous || (tmp->previous && tmp->previous->operator != OP_PIPE))
			child(mini, tmp, 0);
		else if (tmp->next && tmp->operator == OP_PIPE)
			child(mini, tmp, 1);
		else if (!tmp->next || (tmp->next && tmp->next->operator != OP_PIPE))
		{
			child(mini, tmp, 2);
			break;
		}
		tmp = tmp->next;
	}
	if (tmp->next)
		return (tmp->next->prev_amp = AMP_SUCCESS, tmp->next->prev_or = OR_SUCCESS, tmp);
	return (tmp);
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	mini->saved_stdin = dup(0);
    mini->saved_stdout = dup(1);
	if (tmp->operator == OP_PIPE)
		return (ft_set_next(mini, ft_pipe(mini, tmp)));
	// else if (tmp->operator == OP_SUP || tmp->operator == OP_2SUP)
	// 	return (from_to(mini, tmp), tmp->next);
	// else
	// 	return (to_from(mini, tmp));
	return (tmp);
}
