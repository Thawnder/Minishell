/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:54:19 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/10 15:20:42 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_args(char *line)
{
	char	**argv;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (line && line[++i])
		if (line[i] == ' ')
			size++;
	size++;
	argv = ft_calloc(size + 1, sizeof(char *));
	return (argv);
}

void	ft_exec(t_mini *mini, char *line)
{
	char	**argv;
	int		i;
	int		j;
	int		k;

	j = 0;
	argv = init_args(line);
	k = -1;
	i = -1;
	while (line && line[++i])
	{
		if (line[i] == ' ' && i++)
		{
			argv[++k] = ft_strndup(&line[i - j - 1], j);
			j = 0;
		}
		j++;
	}
	if (!line[i])
		argv[++k] = ft_strndup(&line[i - j], j);
	argv[++k] = 0;
	execve(argv[0], argv, mini->env);
}

void	update_result(t_mini *mini, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		mini->result_value = WEXITSTATUS(status);
}

void	ft_fork(t_mini *mini, char *line, int pipe, pid_t pid)
{
	if (!pid && pipe == 0)
		ft_exec(mini, line);
	else if (!pid && pipe > 0)
	{
		if (pipe == 3)
			dup2(mini->saved_stdout, 1);
		else
			dup2(mini->old_fd[1], 1);
		close(mini->old_fd[0]);
		close(mini->old_fd[1]);
		ft_exec(mini, line);
	}
	if (pipe <= 0)
		update_result(mini, pid);
	else
	{
		add_pid(mini, pid);
		if (pipe == 3)
			dup2(mini->saved_stdin, 0);
		else
			dup2(mini->old_fd[0], 0);
		close(mini->old_fd[0]);
		close(mini->old_fd[1]);
	}
}
