/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:49:20 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/10 11:18:27 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	existing_exec(char *path, char *file)
{
	int	exec;

	exec = 0;
	if (found_command(path, file))
	{
		exec = is_exec(path, file);
		if (exec == 1)
			return (free(path), free(file), 1);
		else if (exec == -1)
			return (free(path), free(file), 2);
		printf("%s%s: Permission denied\n", path, file);
		return (free(path), free(file), 2);
	}
	printf("%s%s: No such file or directory\n", path, file);
	return (free(path), free(file), 2);
}

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
	if (get_env(mini, "PATH") == NULL)
		return (0);
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
	int	i;
	int	y;

	i = 0;
	if (!with_path(tmp->arg))
	{
		if (find_exec(mini, tmp))
			return (1);
	}
	else
	{
		while (tmp->arg[i] && tmp->arg[i] != ' ')
			i++;
		y = i - 1;
		while (tmp->arg[y] && tmp->arg[y] != '/')
			y--;
		if (existing_exec(ft_strndup(tmp->arg, y + 1),
				ft_strndup(&tmp->arg[y + 1], i - (y + 1))) == 1)
			return (1);
		else
			return (2);
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
				return (free(stmp), 2);
			printf("%s: No such file or directory\n", stmp);
			return (free(stmp), 2);
		}
		closedir(dir);
		printf("%s: Is a directory\n", stmp);
		return (free(stmp), 2);
	}
	return (free(stmp), find_replace_exec(mini, tmp));
}
