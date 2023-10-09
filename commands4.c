/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:59 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/09 14:46:46 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_export(t_mini *mini, char *src)
{
	int	i;

	i = 0;
	while (mini->export[i] && ft_strncmp(src, mini->export[i], ft_strlen(src)))
		i++;
	if (!mini->export[i])
		return (NULL);
	return (mini->export[i]);
}

int	idx_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**realloc_add(char **dest, int n, char *add)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = ft_calloc(ft_tab_len(dest) + n + 1, sizeof(char *));
	i = -1;
	j = -1;
	if (add != NULL)
		tmp[++j] = ft_strdup(add);
	while (dest[++i] && i < ft_tab_len(dest) && ++j < ft_tab_len(dest) + n)
	{
		if (add && j > 0 && !ft_strcmp(tmp[j - 1], add)
			&& ft_strncmp(dest[i], add, idx_equal(add)) < 0)
		{
			free(tmp[j - 1]);
			tmp[j - 1] = ft_strdup(dest[i]);
			tmp[j] = ft_strdup(add);
		}
		else if (!add || ft_strncmp(add, dest[i], idx_equal(add)))
			tmp[j] = ft_strdup(dest[i]);
		else
			j--;
		free(dest[i]);
	}
	return (free(dest), tmp);
}

void	add_to_env(t_mini *mini, char *arg)
{
	int		i;
	char	*tmp;

	tmp = ft_strndup(arg, idx_equal(arg));
	if (get_env(mini, tmp) == NULL)
	{
		mini->export = realloc_add(mini->export, 1, arg);
		if (ft_strchr(arg, '='))
		{
			mini->env = realloc_add(mini->env, 1, NULL);
			i = ft_tab_len(mini->env);
			mini->env[i] = ft_strdup(arg);
		}
	}
	else
	{
		mini->export = realloc_add(mini->export, 0, arg);
		i = 0;
		while (mini->env[i] && ft_strncmp(mini->env[i], arg, idx_equal(arg)))
			i++;
		free(mini->env[i]);
		mini->env[i] = ft_strdup(arg);
	}
	free(tmp);
}

void	ft_export(t_mini *m, char *arg)
{
	int	i;

	i = 0;
	if (m->has_operator && m->args->operator == OP_PIPE)
		return ;
	while (m->export[i])
	{
		m->args->result = ft_strjoin(m->args->result, "declare -x \"");
		m->args->result = ft_strjoin(m->args->result, m->export[i++]);
		m->args->result = ft_strjoin(m->args->result, "\"\n");
	}
	if (m->has_operator && m->args->operator == OP_PIPE && arg && arg[0])
		free(m->args->result);
	else
	{
		if (!arg[0])
			printf("%s", m->args->result);
		else
			add_to_env(m, arg + 1);
		free(m->args->result);
		m->result_value = 0;
	}
}
