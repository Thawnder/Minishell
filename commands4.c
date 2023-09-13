/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:59 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:16 by bpleutin         ###   ########.fr       */
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

	i = 0;
	while (dest[i])
		i++;
	tmp = ft_calloc(i + size + 1, sizeof(char *));
	i = -1;
	while (dest[++i])
	{
		if (!add || (ft_strcmp(dest[i], add) < 0
				&& ft_strcmp(dest[i + 1], add) > 0))
		{
			tmp[i] = ft_strdup(dest[i]);
			free(dest[i]);
		}
		else if (!ft_strncmp(dest[i], add, idx_equal(add)))
			tmp[i] = ft_strjoin(ft_strndup(dest[i],
						idx_equal(dest[i])),
					ft_strdup(add + idx_equal(dest[i])));
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
	mini->env[i] = ft_strdup(arg);
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
		m->args->result = ft_strjoin(m->args->result, "declare -x \"");
		m->args->result = ft_strjoin(m->args->result, m->export[i++]);
		m->args->result = ft_strjoin(m->args->result, "\"\n");
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
			add_to_env(m, arg);
	}
}
