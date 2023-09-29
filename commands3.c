/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:10:22 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/29 15:37:03 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_mini *mini, char *src)
{
	int	i;

	i = 0;
	while (mini->env[i] && ft_strncmp(src, mini->env[i], ft_strlen(src)))
		i++;
	if (!mini->env[i])
		return (NULL);
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
			if (ft_strcmp(tmp[i], "..") == 0)
			{
				j = ft_strlen(*res) - 2;
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

void	refresh_path(t_mini *mini, char *path, int size, int i)
{
	ft_memset(mini->env[i] + size, 0, ft_strlen(mini->env[i]) - size);
	mini->env[i] = ft_realloc(mini->env[i], size + ft_strlen(path));
	mini->env[i] = ft_strjoin(mini->env[i], path);
}

void	ft_cd(t_mini *mini, char *path)
{
	int	i;

	i = 0;
	if (mini->has_operator && mini->args->operator == OP_PIPE)
		mini->args->result = NULL;
	else if (path[1] == '.' && !path[2])
		return ;
	else if (chdir(path) != 0)
		error_path_cd(mini, path);
	else if ((!path[0] || (*(++path) == '-' && *(path + 1) == '-')))
	{
		while (ft_strncmp(mini->env[i], "OLDPWD=", 7))
			i++;
		free(mini->oldpath);
		mini->oldpath = ft_strdup(mini->path);
		refresh_path(mini, mini->oldpath, 7, i);
		i = 0;
		while (ft_strncmp(mini->env[i], "PWD=", 4))
			i++;
		free(mini->path);
		mini->path = resolve_path(mini->env[i], path);
		refresh_path(mini, mini->path, 4, i);
	}
}
