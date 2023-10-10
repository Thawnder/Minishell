/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/10 17:40:03 by user             ###   ########.fr       */
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

t_lists	*ft_pipe(t_mini *m, t_lists *t, int stat)
{
	while (t && (t->operator == OP_PIPE
			|| (t->previous && t->previous->operator == OP_PIPE)))
	{
		if (ft_replace(m, t) == -1 || ft_check_advanced(m, t) == -1
			|| !ft_is_builtin(m, t))
		{
			dup2(m->saved_stdout, 1);
			if (dup2(m->saved_stdin, 0), (ft_replace(m, t) == -1
					|| ft_check_advanced(m, t) == -1)
				&& t->next && t->operator != OP_PIPE)
				return (t->next->prev_amp = -1, t->next->prev_or = -1, t);
			else if (t->operator != OP_PIPE)
				return (t);
			t = error_command_pipe(m, t);
			continue ;
		}
		stat = pipe_action(m, t);
		if (stat == 1)
			break ;
		else if (stat == 2)
			continue ;
		t = t->next;
	}
	return (end_pipe(m, t));
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	t_lists	*tmp2;

	tmp2 = tmp;
	if (tmp->operator == OP_PIPE)
		return (ft_set_next(mini, ft_pipe(mini, tmp, 0)));
	else if (tmp->previous && tmp->previous->previous
		&& tmp->previous->previous->operator >= OP_INF
		&& tmp->previous->previous->operator <= OP_2SUP)
		return (ft_set_next(mini, ft_pipe(mini, tmp, 0)));
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
