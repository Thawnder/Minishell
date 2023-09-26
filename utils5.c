/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:48:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/22 10:49:19 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exec(char *path, char *str)
{
	DIR				*dir;
	struct dirent	*dent;
	char			*tmp;

	dir = opendir(path);
	tmp = ft_strjoin_nofree(path, str);
	if (dir == NULL)
		return (free(tmp), closedir(dir), 0);
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (!ft_strcmp(dent->d_name, str))
		{
			if (dent->d_type == DT_DIR)
				return (printf("%s: Is a directory\n", tmp), free(tmp),
					closedir(dir), -1);
			if (access(tmp, X_OK))
				return (free(tmp), closedir(dir), 0);
			return (free(tmp), closedir(dir), 1);
		}
		dent = readdir(dir);
	}
	return (free(tmp), closedir(dir), 0);
}