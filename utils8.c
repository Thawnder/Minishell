/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:12:05 by user              #+#    #+#             */
/*   Updated: 2023/10/10 17:46:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_exe_end(t_mini *mini, int from, int to, t_lists *tmp)
{
	(void)to;
	if ((!tmp->previous || tmp->previous->operator != OP_PIPE)
		&& (tmp->next && tmp->next->operator == OP_PIPE))
	{
		if (from != -1)
			ft_custom_fork(mini, tmp->arg, 1, 1);
		else
			ft_custom_fork(mini, tmp->arg, 1, 0);
	}
	else if (tmp->previous && tmp->previous->operator == OP_PIPE
		&& (!tmp->next || tmp->next->operator != OP_PIPE))
	{
		if (from != -1)
			ft_custom_fork(mini, tmp->arg, 3, 1);
		else
			ft_custom_fork(mini, tmp->arg, 2, 0);
	}
	else
	{
		if (from != -1)
			ft_custom_fork(mini, tmp->arg, 2, 1);
		else
			ft_custom_fork(mini, tmp->arg, 2, 0);
	}
}

t_lists	*end_pipe(t_mini *mini, t_lists *tmp)
{
	wait_pid(mini);
	if (tmp && tmp->next)
		return (tmp->next->prev_amp = AMP_SUCCESS,
			tmp->next->prev_or = OR_SUCCESS, tmp);
	return (tmp);
}

int	pipe_action(t_mini *mini, t_lists *tmp)
{
	if (!tmp->previous || (tmp->previous
			&& tmp->previous->operator != OP_PIPE))
		child(mini, tmp, 0);
	else if (tmp->next && tmp->operator == OP_PIPE)
		child(mini, tmp, 1);
	else if (!tmp->next || (tmp->next && (tmp->operator != OP_PIPE
				&& !(tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))))
	{
		child(mini, tmp, 2);
		return (1);
	}
	else
	{
		tmp = do_chevron(mini, tmp);
		dup2(mini->saved_stdin, 0);
		dup2(mini->saved_stdout, 1);
		return (2);
	}
	return (0);
}

t_lists	*error_command_pipe(t_mini *mini, t_lists *tmp)
{
	pipe(mini->old_fd);
	dup2(mini->old_fd[0], 0);
	close(mini->old_fd[0]);
	close(mini->old_fd[1]);
	tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

void	end_custom_fork(t_mini *mini, int pid, int pipe, int from)
{
	int	status;

	if (pipe == 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(pid))
			mini->result_value = WEXITSTATUS(pid);
	}
	if (pipe > 0)
	{
		add_pid(mini, pid);
		if (pipe == 3)
			dup2(mini->saved_stdin, 0);
		else
			dup2(mini->old_fd[0], 0);
		if (from)
			close(mini->old_fd[0]);
		if (from)
			close(mini->old_fd[1]);
	}
}
