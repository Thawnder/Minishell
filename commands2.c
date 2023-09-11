/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:22:03 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/07 11:19:16 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *dest, int size)
{
	char	*tmp;
	int		len;

	len = ft_strlen(dest);
	tmp = malloc(len + size + 1);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, dest, len + 1);
	free(dest);
	return (tmp);
}

int	size_of_echo(char *line)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
		{
			flag = 1;
			i += 3;
		}
		if (line[i] != 39 && line[i] != 34)
			j++;
		i++;
	}
	if (flag == 0)
		j++;
	return (j);
}

char	*stock_echo(char *line)
{
	int		i;
	int		j;
	char	*res;
	int		flag;

	flag = 0;
	i = 0;
	j = 0;
	res = malloc(size_of_echo(line) + 1);
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
		{
			flag = 1;
			i += 3;
		}
		if (line[i] != 39 && line[i] != 34)
			res[j++] = line[i];
		i++;
	}
	if (flag == 0)
		res[j] = '\n';
	res[++j] = 0;
	return (res);
}

void	ft_echo(t_mini *mini, char *line)
{
	int	flag;

	flag = 0;
	while (*line == ' ')
		line++;
	if (mini->has_operator && mini->args->operator == OP_PIPE)
		mini->args->result = stock_echo(line);
	else
	{
		while (*line != 0)
		{
			if (*line == '-' && *line + 1 == 'n' && *line + 2 == ' ')
			{
				flag = 1;
				line += 3;
			}
			if (*line != 39 && *line != 34)
				write(1, line, 1);
			line++;
		}
		if (flag == 0)
			write(1, "\n", 1);
	}
}
