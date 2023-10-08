/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/05 17:18:36 by bpleutin         ###   ########.fr       */
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
	ft_fork(mini, tmp->arg, pos + 1);
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
			if ((ft_replace(mini, tmp) == -1
					|| ft_check_advanced(mini, tmp) == -1)
				&& tmp->next && tmp->operator != OP_PIPE)
				return (tmp->next->prev_amp = AMP_FALSE
					, tmp->next->prev_or = OR_FALSE, tmp);
			else if (tmp->operator != OP_PIPE)
				return (tmp);
			dup2(STDIN_FILENO, 0);
			dup2(STDOUT_FILENO, 1);
			tmp = tmp->next;
			continue ;
		}
		if (!tmp->previous || (tmp->previous
				&& tmp->previous->operator != OP_PIPE))
			child(mini, tmp, 0);
		else if (tmp->next && tmp->operator == OP_PIPE)
			child(mini, tmp, 1);
		else if (!tmp->next || (tmp->next && (tmp->next->operator != OP_PIPE
			&& !(tmp->next->operator >= OP_INF && tmp->next->operator <= OP_2SUP))))
		{
			fprintf(stderr, "ARG %s\n", tmp->arg);
			child(mini, tmp, 2);
			break ;
		}
		else
		{
			close(mini->new_fd[0]);
			close(mini->new_fd[1]);
			tmp = do_chevron(mini, tmp);
			child(mini, tmp->previous->previous, 0);
			continue ;
		}
		tmp = tmp->next;
	}
	wait_pid(mini);
	if (tmp->next)
		return (tmp->next->prev_amp = AMP_SUCCESS,
			tmp->next->prev_or = OR_SUCCESS, tmp);
	return (tmp);
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	t_lists	*tmp2;

	mini->saved_stdin = dup(0);
	mini->saved_stdout = dup(1);
	tmp2 = tmp;
	if (tmp->operator == OP_PIPE)
		return (ft_set_next(mini, ft_pipe(mini, tmp)));
	if (tmp2->operator >= OP_INF && tmp2->operator <= OP_2SUP)
	{
		while (tmp2->operator >= OP_INF && tmp2->operator <= OP_2SUP)
		{
			if (tmp2->operator == OP_SUP || tmp2->operator == OP_2SUP)
				from_to(mini, tmp, tmp2->operator, tmp2->next);
			else
				to_from(mini, tmp, tmp2->operator, tmp2->next);
			tmp2 = tmp2->next;
		}
		tmp = tmp2->next;
		if (!tmp)
			return (NULL);		
	}
	return (tmp);
}
