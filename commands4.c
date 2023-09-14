/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:59 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/14 13:53:33 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	idx_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**ft_tab_realloc(char **dest, int size, char *add)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(ft_tab_len(dest) + size + 1, sizeof(char *));
	i = -1;
	while (++i < ft_tab_len(dest) + size)
	{
		if (!add || ((i < ft_tab_len(dest) - 1 && !(ft_strcmp(dest[i], add) < 0
						&& ft_strcmp(dest[i + 1], add) > 0))
				|| (i == ft_tab_len(dest) - 1 && ft_strcmp(dest[i], add) < 0)))
		{
			if (dest[i])
				tmp[i] = ft_strdup(dest[i]);
			if (dest[i])
				free(dest[i]);
		}
		else if (i < ft_tab_len(dest)
			&& !ft_strncmp(dest[i], add, idx_equal(add)))
			tmp[i] = ft_strjoin(ft_strndup(dest[i], idx_equal(dest[i])),
					add + idx_equal(dest[i]));
		else
			tmp[i] = ft_strdup(add);
	}
	return (free(dest), tmp);
}

void	add_to_env(t_mini *mini, char *arg)
{
	int	i;

	i = 0;
	mini->env = ft_tab_realloc(mini->env, 1, NULL);
	while (mini->env[i])
		i++;
	mini->env[i++] = ft_strdup(arg);
	mini->env[i] = 0;
	mini->export = ft_tab_realloc(mini->export, 1, arg);
}

void	print_export(t_mini *m)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (m->export[i])
	{
		printf("%d:%s\n", i, m->export[i]);
		tmp = ft_strjoin(tmp, "declare -x \"");
		tmp = ft_strjoin(tmp, m->export[i++]);
		tmp = ft_strjoin(tmp, "\"\n");
	}
	printf("%s", tmp);
	free(tmp);
}

void	ft_export(t_mini *m, char *arg)
{
	int	i;

	i = 0;
	if (m->has_operator && m->args->operator == OP_PIPE)
	{
		if (!arg[0])
		{
			while (m->export[i])
			{
				m->args->result = ft_strjoin(m->args->result, "declare -x \"");
				m->args->result = ft_strjoin(m->args->result, m->export[i++]);
				m->args->result = ft_strjoin(m->args->result, "\"\n");
			}
		}
		else
			m->args->result = NULL;
	}
	else
	{
		if (!arg[0])
			print_export(m);
		else
			add_to_env(m, arg + 1);
	}
}
