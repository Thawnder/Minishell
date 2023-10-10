/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:20:59 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/10 14:34:05 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*send_end(char *old)
{
	int		i;
	int		y;
	char	*str;

	i = ft_strlen(old) - 2;
	if (i < 0)
		i = 0;
	while (i >= 0 && old[i] && old[i] != '\n')
		i--;
	str = ft_calloc(i + 2, sizeof(char));
	y = 0;
	i++;
	while (y < i)
	{
		str[y] = old[y];
		y++;
	}
	return (free(old), str);
}

int	cmp_end(char *str, char *end)
{
	int	i;
	int	y;

	y = 0;
	i = ft_strlen(str) - 2;
	if (i < 0)
		i = 0;
	while (i >= 0 && str[i] && str[i] != '\n')
		i--;
	i++;
	if (str[i] == '\n')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' && !end[y])
			return (1);
		if (str[i] != end[y])
			return (0);
		else
			y++;
		i++;
	}
	return (0);
}

char	*ft_realloc_buff(char *buf, char tmp[1], int btotal)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_calloc(btotal + 1, sizeof(char));
	while (i < btotal)
	{
		if (buf[i] != '\0')
			str[i] = buf[i];
		else
			str[i] = tmp[0];
		i++;
	}
	free(buf);
	return (str);
}

int	file_exist(t_mini *mini, char *file)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir((get_env(mini, "PWD") + 4));
	if (dir == NULL)
		return (closedir(dir), 0);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (!ft_strcmp(dent->d_name, file))
			return (closedir(dir), 1);
		dent = readdir(dir);
	}
	return (closedir(dir), 0);
}
