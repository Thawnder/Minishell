/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:51:54 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/04 12:59:38 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_command(char *path, char *str)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir == NULL)
		return (closedir(dir), 0);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (!ft_strcmp(dent->d_name, str))
			return (closedir(dir), 1);
		dent = readdir(dir);
	}
	return (closedir(dir), 0);
}

char	*get_path(char **tab, char *tmp)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (tab[++i])
	{
		if (found_command(tab[i], tmp))
		{
			str = ft_strdup(tab[i]);
			return (free_tabl(tab), str);
		}
	}
	return (free_tabl(tab), NULL);
}

int	with_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	has_option_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] && str[++i] && str[i + 1]
		&& str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
