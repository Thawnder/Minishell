/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:33:30 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 13:24:16 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dollars(t_mini *mini, char *old, int i, int y)
{
	int		z;
	char	*str;
	char	*tmp;

	while (old[i] && i <= y && old[i] != '$')
		i++;
	if (old[i + 1] == '{')
		i += 2;
	else
		i++;
	z = i;
	while (old[z] && z < y && old[z] != '}' && old[z] != '$'
		&& old[z] != ' ' && old[z] != '"' && old[z] != '\'')
		z++;
	tmp = ft_strndup(&old[i], z - i);
	if (!get_env(mini, tmp) && !ft_strcmp(tmp, "?"))
		return (free(tmp), ft_itoa(mini->result_value));
	else if (!get_env(mini, tmp))
		return (free(tmp), NULL);
	str = ft_strdup(get_env(mini, tmp) + z - i + 1);
	return (free(tmp), str);
}

int	has_dollar(char	*old, int i, int y)
{
	int	count;

	count = 0;
	while (old[i] && i <= y)
	{
		if (old[i] == '$' && old[i + 1] != ' ')
		{
			i++;
			count++;
			while (old[i] && old[i] != '}' && old[i] != '$'
				&& old[i] != ' ' && old[i] != '"' && old[i] != '\'')
			{
				i++;
				count++;
			}
			return (count);
		}
		i++;
	}
	return (0);
}

char	*manage_dollars(t_mini *mini, char *old, int i, int y)
{
	char	*tmp;
	char	*str;
	int		a;
	int		z;
	int		p;

	a = 0;
	z = 0;
	p = -1;
	tmp = get_dollars(mini, old, i, y);
	str = ft_calloc(ft_strlen(old) + ft_strlen(tmp) - has_dollar(old, i, y) + 1,
			sizeof(char));
	while (old[z] && old[z] != '$')
		str[a++] = old[z++];
	z += has_dollar(old, i, y);
	while (tmp && tmp[++p])
		str[a++] = tmp[p];
	while (old[z])
		str[a++] = old[z++];
	return (free(tmp), str);
}

static char	*delete_quotes(t_mini *mini, char *old, int i, int y)
{
	char	*str;

	if (old[i] == '\'' || (old[i] == '"' && !has_dollar(old, i, y)))
	{
		str = strdup_without(old, i, y);
	}
	else if (old[i] != '\'')
	{
		while (has_dollar(old, i, y) || str[y] != '"')
		{
			str = manage_dollars(mini, old, i, y);
			y = i;
			while (str[y] != '"')
				y++;
		}
	}
	else
		str = strdup_without(old, i, y);
	return (free(old), str);
}

void	find_quotes(t_mini *mini, t_lists *tmp)
{
	int		i;
	int		y;
	char	c;
	int		z;

	i = 0;
	z = 0;
	while (tmp->arg[i])
	{
		if (z < 2 && (tmp->arg[i] == '"' || tmp->arg[i] == '\''))
		{
			c = tmp->arg[i];
			y = i + 1;
			while (tmp->arg[y] && tmp->arg[y] != c)
				y++;
			if (tmp->arg[y] == '\'')
				z++;
			tmp->arg = delete_quotes(mini, tmp->arg, i, y);
			i = -1;
			z++;
		}
		i++;
	}
}
