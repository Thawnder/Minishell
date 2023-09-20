/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:49:20 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/20 17:02:41 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_exec(t_mini *mini, t_lists *tmp)
{
	int		i;
	int		y;
	char	*str;
	char	*path;

	i = 0;
	while (tmp->arg[i] && tmp->arg[i] != ' ')
		i++;
	str = ft_strndup(tmp->arg, i);
	path = get_path(ft_split((get_env(mini, "PATH") + 5), ':'), str);
	if (path == NULL)
		return (free(str), 0);
	path = ft_strjoin(ft_strjoin(path, "/"), str);
	free(str);
	str = ft_calloc(ft_strlen(path) + ft_strlen(tmp->arg) + 1, sizeof(char));
	y = -1;
	while (path[++y])
		str[y] = path[y];
	while (tmp->arg[i])
		str[y++] = tmp->arg[i++];
	free(tmp->arg);
	tmp->arg = str;
	return (free(path), 1);
}

int	find_replace_exec(t_mini *mini, t_lists *tmp)
{
	if (!with_path(tmp->arg))
	{
		if (find_exec(mini, tmp))
			return (1);
	}
	return (0);
}

int	try_prev_path(char *str)
{
	char	*tmp;
	int		i;
	DIR		*dir;

	i = ft_strlen(str) - 2;
	while (str[i] && str[i] != '/')
		--i;
	tmp = ft_strndup(str, i);
	dir = opendir(tmp);
	if (dir == NULL)
		return (free(tmp), 0);
	closedir(dir);
	printf("%s: Not a directory\n", &str[i]);
	return (free(tmp), 1);
}

int	try_path(t_mini *mini, t_lists *tmp)
{
	char	*stmp;
	int		i;
	DIR		*dir;

	i = 0;
	while (tmp->arg[i] && tmp->arg[i] != ' ')
		i++;
	stmp = ft_strndup(tmp->arg, i);
	if (stmp[ft_strlen(stmp) - 1] == '/')
	{
		dir = opendir(stmp);
		if (dir == NULL)
		{
			if (try_prev_path(stmp))
				return (free(stmp), 0);
			printf("%s: No such file or directory\n", stmp);
			return (free(stmp), 2);
		}
		closedir(dir);
		printf("%s: Is a directory\n", stmp);
		return (free(stmp), 2);
	}
	return (free(stmp), find_replace_exec(mini, tmp));
}
