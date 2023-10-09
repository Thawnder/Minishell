/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:48:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 15:25:18 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lists	*ft_set_next(t_mini *mini, t_lists *tmp)
{
	if (!tmp)
		return (NULL);
	if (!tmp->next)
		return (tmp);
	tmp = tmp->next;
	if (tmp->previous->operator == OP_2PIPE && ((tmp->prev_or == OR_SUCCESS
				&& tmp->previous && !(tmp->previous->operator == OP_2AMP))
			|| tmp->prev_amp == AMP_SUCCESS))
		tmp = delete_till_end(tmp, tmp->previous->operator,
				tmp->priorities, 1);
	else if (tmp->previous->operator == OP_2AMP && (tmp->prev_or == OR_FALSE
			|| tmp->prev_amp == AMP_FALSE))
		tmp = delete_till_end(tmp, tmp->previous->operator,
				tmp->priorities, -1);
	while (tmp && (tmp->previous->operator == OP_2PIPE
			|| tmp->previous->operator == OP_2AMP))
	{
		if (tmp->previous->operator == OP_2PIPE)
			tmp = process_or(mini, tmp);
		else if (tmp->previous->operator == OP_2AMP)
			tmp = process_amp(mini, tmp);
	}
	return (tmp);
}

void	error_path_cd(t_mini *mini, char *path)
{
	printf("cd: not a directory:%s\n", path);
	mini->result_value = 1;
}

t_lists	*send_command(t_mini *mini, t_lists *tmp)
{
	if (tmp->operator == OP_PIPE
		|| (tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))
		return (special_operator(mini, tmp));
	else if (tmp->previous && tmp->previous->previous
			&& tmp->previous->previous->operator >= OP_INF
			&& tmp->previous->previous->operator <= OP_2SUP)
		return (special_operator(mini, tmp));
	else
		return (ft_command(mini, tmp), tmp);
	return (NULL);
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
