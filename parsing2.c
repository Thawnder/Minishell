/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/10 15:16:26 by bpleutin         ###   ########.fr       */
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
	pid_t	pid;

	if (pipe(mini->old_fd) < 0)
		return ;
	g_forked = 1;
	pid = fork();
	ft_fork(mini, tmp->arg, pos + 1, pid);
	g_forked = 0;
}

t_lists	*ft_pipe(t_mini *mini, t_lists *tmp)
{
	while (tmp && (tmp->operator == OP_PIPE
			|| (tmp->previous && tmp->previous->operator == OP_PIPE)))
	{
		if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
			|| !ft_is_builtin(mini, tmp))
		{
			dup2(mini->saved_stdout, 1);
			if (dup2(mini->saved_stdin, 0), (ft_replace(mini, tmp) == -1
					|| ft_check_advanced(mini, tmp) == -1)
				&& tmp->next && tmp->operator != OP_PIPE)
				return (tmp->next->prev_amp = AMP_FALSE
					, tmp->next->prev_or = OR_FALSE, tmp);
			else if (tmp->operator != OP_PIPE)
				return (tmp);
			pipe(mini->old_fd);
			dup2(mini->old_fd[0], 0);
			close(mini->old_fd[0]);
			close(mini->old_fd[1]);
			tmp = tmp->next;
			continue ;
		}
		if (!tmp->previous || (tmp->previous
				&& tmp->previous->operator != OP_PIPE))
			child(mini, tmp, 0);
		else if (tmp->next && tmp->operator == OP_PIPE)
			child(mini, tmp, 1);
		else if (!tmp->next || (tmp->next && (tmp->operator != OP_PIPE
			&& !(tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))))
		{
			fprintf(stderr, "ARG %s\n", tmp->arg);
			child(mini, tmp, 2);
			break ;
		}
		else
		{
			fprintf(stderr, "LASTO pour %s\n", tmp->arg);
			tmp = do_chevron(mini, tmp);
			dup2(mini->saved_stdin, 0);
			dup2(mini->saved_stdout, 1);
			continue ;
		}
		tmp = tmp->next;
	}
	wait_pid(mini);
	if (tmp && tmp->next)
		return (tmp->next->prev_amp = AMP_SUCCESS,
			tmp->next->prev_or = OR_SUCCESS, tmp);
	return (tmp);
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	t_lists	*tmp2;

	tmp2 = tmp;
	if (tmp->operator == OP_PIPE)
		return (ft_set_next(mini, ft_pipe(mini, tmp)));
	 else if (tmp->previous && tmp->previous->previous
	 		&& tmp->previous->previous->operator >= OP_INF
	 		&& tmp->previous->previous->operator <= OP_2SUP)
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
		tmp = tmp2;
		wait_pid(mini);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}
