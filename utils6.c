/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:20:59 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/05 16:50:25 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*send_end(char *old)
{
	int		i;
	int		y;
	char	*str;

	i = ft_strlen(old) - 2;
	while (old[i] && old[i] != '\n')
		i--;
	str = calloc(i, sizeof(char));
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
	while (str[i] && str[i] != '\n')
		i--;
	i++;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		if (str[i] != end[y])
			return (0);
		i++;
		y++;
	}
	return (0);
}

char	*ft_realloc_buff(char *buf, char tmp[1], int btotal)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_calloc(sizeof(char), btotal + 1);
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

void	child_between_pipe(t_mini *mini, t_lists *tmp)
{
	dup2(mini->new_fd[0], 0);
	dup2(mini->old_fd[1], 1);
	ft_fork(mini, tmp->arg);
	close(mini->new_fd[0]);
	close(mini->old_fd[1]);
}
