/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:00:19 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/04 15:38:33 by ldeville         ###   ########.fr       */
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
	ft_printf("\nheredoc> ");
	while (!done && read(0, tmp, 1))
	{
		len++;
		buf = ft_realloc_buff(buf, tmp, len);
		if (tmp[0] == '\n')
		{
			if (cmp_end(buf, end))
				return (printf("\n"), send_end(buf));
			ft_printf("\nheredoc> ");
		}
	}
	return (buf);
}


int	read_from_shell(char *end)
{
	char	*str;

	str = ft_clone_terminal(end);
	ft_printf("%s\n", str);
	free(str);
	return (0);
	
}

void	exec_command(t_mini *mini, int from, int to, t_lists *tmp)
{
	if (from != -1)
		dup2(from, 0);
	else
		dup2(to, 1);
	ft_fork(mini, tmp->arg);
	if (from != -1)
		close(from);
	else
		close(to);
}

t_lists *from_to(t_mini *mini, t_lists *tmp)
{
	int		file;
	char	*path;
	char	*nfile;

	nfile = ft_strjoin_nofree("/", tmp->next->arg);
	path = ft_strjoin_nofree(get_env(mini, "PWD") + 4, nfile);
	ft_printf("PATH %s\n", path);
	if (!file_exist(mini, tmp->next->arg))
		file = open(path, O_WRONLY | O_CREAT, 0644);
	else if (tmp->operator == OP_SUP)
		file = open(path, O_WRONLY | O_TRUNC, 0644);
	else
		file = open(path, O_WRONLY| O_APPEND);

	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
			|| !ft_is_builtin(mini, tmp))
		return (free(nfile), free(path), close(file), tmp->next->next);
	exec_command(mini, -1, file, tmp);
	close(file);
	dup2(mini->saved_stdin, 0);
	dup2(mini->saved_stdout, 1);
	return (free(nfile), free(path), tmp->next->next);
}

t_lists *to_from(t_mini *mini, t_lists *tmp)
{
	int		file;
	char	*path;
	char	*nfile;

	if (tmp->operator == OP_INF && !file_exist(mini, tmp->next->arg))
	{
		printf("no such file or directory: %s", tmp->next->arg);
		return (tmp->next->next);
	}
	nfile = ft_strjoin_nofree("/", tmp->next->arg);
	path = ft_strjoin_nofree(get_env(mini, "PWD") + 4, nfile);
	if (tmp->operator == OP_INF)
		file = open(path, O_RDONLY);
	else
		file = read_from_shell(tmp->next->arg);

	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1
			|| !ft_is_builtin(mini, tmp))
		return (free(nfile), free(path), close(file), tmp->next->next);
	exec_command(mini, file, -1, tmp);
	close(file);
	dup2(mini->saved_stdin, 0);
	dup2(mini->saved_stdout, 1);
	return (free(nfile), free(path), tmp->next->next);
}