/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:10:22 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/12 16:13:30 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_mini *mini, char *src)
{
	int	i;

	i = 0;
	while (mini->env[i] && ft_strncmp(src, mini->env[i], ft_strlen(src)))
		i++;
	return (mini->env[i]);
}

void	fill_path(char **res, char *path)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = ft_split(path, '/');
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], ".", 1) == 0)
		{
			if (ft_strncmp(tmp[i], "..", 2) == 0)
			{
				j = ft_strlen(*res);
				while (j && (*res)[j] != '/')
					j--;
				*res = free_substr(*res, 0, j);
			}
		}
		else
			*res = ft_strjoin(*res, tmp[i]);
		if (tmp[i + 1] != NULL)
			*res = ft_strjoin(*res, "/");
		i++;
	}
}

char	*resolve_path(char *pwd, char *path)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (!path[i] || (path[i] == '-' && path[++i] == '-' && i++))
		res = ft_strdup(getenv("HOME"));
	if (!path[i])
		return (chdir(getenv("HOME")), res);
	else if (path[i] == '/')
	{
		while (path[i] && path[i + 1] != '.')
			i++;
		res = ft_strndup(path, i);
	}
	if (!res)
	{
		res = ft_strdup(pwd + 4);
		if (!(path[0] == '.' && path[1] == '.'))
			res = ft_strjoin(res, "/");
	}
	if (res[ft_strlen(res) - 1] != '/' && path[i] == '/' && i++)
		res = ft_strjoin(res, "/");
	return (fill_path(&res, path + i), res);
}

void	ft_cd(t_mini *mini, char *path)
{
	int	i;

	i = 0;
	if (mini->has_operator && mini->args->operator == OP_PIPE)
		mini->args->result = NULL;
	else if (path[1] == '.' && !path[2])
		return ;
	else if (!path[0] || chdir(++path) == 0)
	{
		while (ft_strncmp(mini->env[i], "OLDPWD=", 7))
			i++;
		free(mini->oldpath);
		mini->oldpath = ft_strdup(mini->path);
		ft_memset(mini->env[i] + 7, 0, ft_strlen(mini->env[i]) - 7);
		mini->env[i] = ft_realloc(mini->env[i], 7 + ft_strlen(mini->oldpath));
		mini->env[i] = ft_strjoin(mini->env[i], mini->oldpath);
		i = 0;
		while (ft_strncmp(mini->env[i], "PWD=", 4))
			i++;
		free(mini->path);
		mini->path = resolve_path(mini->env[i], path);
		ft_memset(mini->env[i] + 4, 0, ft_strlen(mini->env[i]) - 4);
		mini->env[i] = ft_realloc(mini->env[i], 4 + ft_strlen(mini->path));
		mini->env[i] = ft_strjoin(mini->env[i], mini->path);
	}
}
