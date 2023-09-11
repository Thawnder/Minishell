/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:10:22 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/07 17:37:06 by bpleutin         ###   ########.fr       */
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

void	fill_path(char *res, char *path)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = ft_split(path, '/');
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], ".", 2) != 0)
		{
			if (!ft_strncmp(tmp[i], "..", 3))
			{
				j = ft_strlen(res);
				while (j && res[j] != '/')
					j--;
				res = free_substr(res, 0, j);
			}
			else
				res = ft_strjoin(res, tmp[i]);
			if (tmp[i + 1])
				res = ft_strjoin(res, "/");
		}
		i++;
	}
}

char	*resolve_path(char *path)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if ((!path[i] || path[i] == '~' || (path[i] == '-' && path[++i] == '-')) && i++)
		res = ft_strdup(getenv("HOME"));
	else if (path[i] == '/')
	{
		while (path[i] && path[i + 1] != '.')
			i++;
		res = ft_strndup(path, i);

	}
	if (path[i] == '/' && i++)
		res = ft_strjoin(res, "/");
	fill_path(res, path + i);
	printf("res after fill: %s\n", res); // null; y'a un truc a corriger dans fill path
	// et faut rajouter le debut du pwd
	return (res);
}

void	ft_cd(t_mini *mini, char *path)
{
	int	i;

	i = 0;
	while (*path == ' ')
		path++;
	if (mini->has_operator && mini->args->operator == OP_PIPE)
		mini->args->result = NULL;
	else if (chdir(path) == 0)
	{
		free(mini->oldpath);
		mini->oldpath = ft_strjoin_nofree("OLDPWD=", mini->path);
		while (ft_strncmp(mini->env[i], "OLDPWD=", 7))
			i++;
		ft_memcpy(mini->env[i], mini->oldpath, ft_strlen(mini->oldpath));
		i = 0;
		free(mini->path);
		mini->path = resolve_path(path);
		while (ft_strncmp(mini->env[i], "PWD=", 4))
			i++;
		ft_memcpy(mini->env[i], mini->path, ft_strlen(mini->path));
	}
	else
		printf("cd: gros chien de la casse t'as cru t'allais me douiller?\n");
}
