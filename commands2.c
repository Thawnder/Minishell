/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:22:03 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/11 12:23:14 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (flag != 2 && check_flag(&line[i]) != 0)
		{
			flag = 1;
			i += check_flag(&line[i]);
		}
		res[j++] = line[i++];
		if (flag != 1)
			flag = 2;
	}
	if (flag == 0 || flag == 2)
		res[j] = '\n';
	res[++j] = 0;
	return (res);
}

void	ft_echo(t_mini *mini, char *line)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	mini->result_value = 0;
	if (mini->has_operator && (mini->args->operator == OP_SUP
			|| mini->args->operator == OP_2SUP))
		mini->args->result = stock_echo(line);
	else
	{
		while (line[i])
		{
			if (flag != 2 && check_flag(&line[0]) != 0)
				i += check_flag(&line[i]);
			if (flag != 2 && check_flag(&line[0]) != 0)
				flag = 1;
			write(1, &line[i++], 1);
			if (flag != 1)
				flag = 2;
		}
		if (flag == 1)
			return (g_forked = 2, (void)0);
		write(1, "\n", 1);
	}
}

char	**realloc_remove(char **dest, int n, char *arg)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_calloc(ft_tab_len(dest) - n + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (dest[++i])
	{
		if (i < ft_tab_len(dest) - 1
			&& !ft_strncmp(dest[i], arg, ft_strlen(arg)))
			free(dest[i++]);
		if (ft_strncmp(dest[i], arg, ft_strlen(arg)))
			tmp[j++] = ft_strdup(dest[i]);
		free(dest[i]);
	}
	return (free(dest), tmp);
}

void	ft_unset(t_mini *m, char *arg)
{
	char	*tmp;

	if (arg && arg[0] && !(m->has_operator && m->args->operator == OP_PIPE))
	{
		if (ft_strchr(arg, '='))
			tmp = ft_strjoin_nofree(arg + 1, "=");
		else
			tmp = ft_strdup(arg + 1);
		if (get_env(m, tmp) != NULL)
			m->env = realloc_remove(m->env, 1, tmp);
		if (get_export(m, tmp) != NULL)
			m->export = realloc_remove(m->export, 1, tmp);
		free(tmp);
		m->result_value = 0;
	}
}
