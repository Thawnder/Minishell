/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:00:19 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 15:18:12 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clone_terminal(char *end)
{
	char	*buf;
	char	tmp[1];
	int		len;
	int		done;

	done = 0;
	buf = ft_calloc(sizeof(char), 1);
	len = 0;
	ft_printf("heredoc> ");
	while (!done && read(0, tmp, 1))
	{
		len++;
		buf = ft_realloc_buff(buf, tmp, len);
		if (tmp[0] == '\n')
		{
			if (cmp_end(buf, end))
				return (printf("\n"), send_end(buf));
			ft_printf("heredoc> ");
		}
	}
	return (buf);
}


int	read_from_shell(t_mini *mini, char *end)
{
	char	*str;

	if (pipe(mini->new_fd) < 0)
		return (0);
	str = ft_clone_terminal(end);
	ft_printf("READING = |%s|\n", str);
	ft_putstr_fd(str, mini->new_fd[1]);
	close(mini->new_fd[1]);
	free(str);
	mini->old_fd[0] = mini->new_fd[0];
	return (mini->old_fd[0]);
}

void	exec_command(t_mini *mini, int from, int to, t_lists *tmp)
{
	if (from != -1)
	{
		if (pipe(mini->new_fd) < 0)
			return ;
		dup2(from, 0);
		mini->old_fd[0] = mini->new_fd[0];
		mini->old_fd[1] = mini->new_fd[1];
	}
	if (to != -1)
	{
		mini->old_fd[1] = to;
		mini->old_fd[0] = from;
	}
	if ((!tmp->previous || tmp->previous->operator != OP_PIPE)
		&& (!tmp->next || tmp->next->operator != OP_PIPE))
	{
		if (from != -1)
			ft_custom_fork(mini, tmp->arg, 3, 1);
		else
			ft_custom_fork(mini, tmp->arg, 2, 0);
	}
	else if ((!tmp->previous || tmp->previous->operator != OP_PIPE)
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

t_lists	*from_to(t_mini *mini, t_lists *tmp, t_operator op, t_lists *tmp2)
{
	int		file;
	char	*path;
	char	*nfile;

	nfile = ft_strjoin_nofree("/", tmp2->arg);
	path = ft_strjoin_nofree(get_env(mini, "PWD") + 4, nfile);
	if (!file_exist(mini, tmp2->arg))
		file = open(path, O_RDWR | O_CREAT, 0644);
	else if (op == OP_SUP)
		file = open(path, O_RDWR | O_TRUNC, 0644);
	else
		file = open(path, O_RDWR | O_APPEND);
	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
		|| !ft_is_builtin(mini, tmp))
		return (free(nfile), free(path), close(file), tmp2->next);
	exec_command(mini, -1, file, tmp);
	close(file);
	if (tmp2->operator == OP_PIPE)
	{
		pipe(mini->old_fd);
		close(mini->old_fd[0]);
		mini->old_fd[0] = open(path, O_RDONLY);
		dup2(mini->old_fd[0], 0);
	}
	return (free(nfile), free(path), tmp2->next);
}

t_lists	*to_from(t_mini *mini, t_lists *tmp, t_operator op, t_lists *tmp2)
{
	int		file;
	char	*path;
	char	*nfile;

	if (op == OP_INF && !file_exist(mini, tmp2->arg))
		return (printf("no such file or directory: %s\n", tmp2->arg),
			tmp2->next);
	nfile = ft_strjoin_nofree("/", tmp2->arg);
	path = ft_strjoin_nofree(get_env(mini, "PWD") + 4, nfile);
	if (op == OP_INF)
		file = open(path, O_RDONLY);
	else
		file = read_from_shell(mini, tmp2->arg);
	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
		|| !ft_is_builtin(mini, tmp))
	{
		if (op == OP_INF)
			return (free(nfile), free(path), close(file), tmp2->next);
		return (free(nfile), free(path), close(file),
			close(mini->old_fd[0]),
			tmp2->next);
	}
	exec_command(mini, file, -1, tmp);
	if (op == OP_INF)
		return (free(nfile), free(path), close(file), tmp2->next);
	return (free(nfile), free(path),
	close(file), tmp2->next);
}
