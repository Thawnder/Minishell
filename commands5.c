/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:54:19 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/02 13:35:48 by bpleutin         ###   ########.fr       */
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
	free_tabl(argv);
}

void	ft_fork(t_mini *mini, char *line)
{
	int	status;

	g_forked = 1;
	if (fork() == 0)
		ft_exec(mini, line);
	waitpid(0, &status, 0);
	g_forked = 0;
}
