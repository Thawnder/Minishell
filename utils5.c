/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:48:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/29 16:37:39 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	send_next_status(t_lists *tmp, int op, int status, int prio)
{
	tmp = tmp->next;
	if (!tmp)
		return ;
	while (tmp && tmp->priorities != prio)
	{

	}

}*/

void	error_path_cd(t_mini *mini, char *path)
{
	printf("cd: not a directory:%s\n", path);
	mini->result_value = 1;
}

void	send_command(t_mini *mini, t_lists *tmp)
{
	if (tmp->operator == OP_PIPE
		|| (tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))
		special_operator(mini, tmp);
	else
		ft_command(mini, tmp);
}

void	add_is_pipe(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->previous && tmp->is_pipe)
			tmp->previous->is_pipe = 1;
		tmp = tmp->previous;
	}
}

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
