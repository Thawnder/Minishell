/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:54:19 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/18 10:28:28 by bpleutin         ###   ########.fr       */
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
	argv = ft_calloc(size + 1, sizeof(char *));
	return (argv);
}

void	ft_exec(t_mini *mini, char *line)
{
	char	**argv;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	argv = init_args(line);
	k = 0;
	while (line && line[++i])
	{
		if (line[i] == ' ')
		{
			argv[k] = ft_strndup(&line[i], j);
			printf("argv[%d]=%s\n", k, argv[k]);
			j = 0;
			k++;
		}
		j++;
	}
	execve(argv[0], argv, mini->env);
	free_tabl(argv);
}
