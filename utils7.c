/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:29:31 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/11 13:56:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_custom_fork(t_mini *mini, char *line, int pipe, int from)
{
	pid_t	pid;

	g_forked = 1;
	pid = fork();
	if (!pid && pipe > 0)
	{
		if (pipe == 3)
			dup2(mini->saved_stdout, 1);
		else
			dup2(mini->old_fd[1], 1);
		if (from)
			close(mini->old_fd[0]);
		if (from)
			close(mini->old_fd[1]);
		ft_exec(mini, line);
	}
	end_custom_fork(mini, pid, pipe, from);
	g_forked = 0;
}

int	is_quoted(char *str, int i)
{
	int	a;

	a = 0;
	if (str[i] && str[i] == '"')
	{
		a = 1;
		while (str[i + a] && str[i + a] != '"')
			a++;
	}
	else if (str[i] && str[i] == '\'')
	{
		a = 1;
		while (str[i + a] && str[i + a] != '\'')
			a++;
	}
	return (a);
}

void	wait_pid(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	if (!mini->pid)
		return ;
	while (mini->pid && mini->pid[i] != 0)
		waitpid(mini->pid[i++], &status, 0);
	if (mini->pid)
		free(mini->pid);
	mini->pid = NULL;
}

void	add_pid(t_mini *mini, int pid)
{
	int	i;
	int	*new;

	i = 0;
	if (!mini->pid)
	{
		mini->pid = calloc(2, sizeof(int));
		mini->pid[i] = pid;
		return ;
	}
	while (mini->pid[i])
		i++;
	new = calloc(i + 2, sizeof(int));
	i = 0;
	while (mini->pid[i])
	{
		new[i] = mini->pid[i];
		i++;
	}
	new[i] = pid;
	free(mini->pid);
	mini->pid = new;
}

t_lists	*do_chevron(t_mini *mini, t_lists *tmp)
{
	t_lists	*tmp2;

	tmp2 = tmp;
	while (tmp2 && tmp2->operator >= OP_INF && tmp2->operator <= OP_2SUP)
	{
		if (tmp2->operator == OP_SUP || tmp2->operator == OP_2SUP)
			from_to(mini, tmp, tmp2->operator, tmp2->next);
		else
			to_from(mini, tmp, tmp2->operator, tmp2->next);
		tmp2 = tmp2->next;
	}
	return (tmp2->next);
}
