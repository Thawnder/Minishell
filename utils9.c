/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:29:07 by user              #+#    #+#             */
/*   Updated: 2023/10/12 09:57:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_next_pipe(t_mini *mini, t_lists *tmp)
{
	if (tmp->previous->previous->operator == OP_SUP
		|| tmp->previous->previous->operator == OP_2SUP)
	{
		close(mini->old_fd[0]);
		close(mini->old_fd[1]);
	}
}

t_lists	*get_end_chevron(t_lists **tmp)
{
	t_lists	*tmp2;

	tmp2 = *tmp;
	while (tmp2 && tmp2->operator >= OP_INF && tmp2->operator <= OP_2SUP)
		tmp2 = tmp2->next;
	*tmp = tmp2->next;
	return (tmp2->next);
}

void	ft_need_space(char *str, char *old_str, int *i, int *y)
{
	if (old_str[*i - 1] == '"')
	{
		while (old_str[*i] && old_str[*i] != '"')
		{
			str[*y] = old_str[*i];
			*y += 1;
			*i += 1;
		}
		str[*y] = old_str[*i];
		*y += 1;
		*i += 1;
	}
	else if (old_str[*i - 1] == '\'')
	{
		while (old_str[*i] && old_str[*i] != '\'')
		{
			str[*y] = old_str[*i];
			*y += 1;
			*i += 1;
		}
		str[*y] = old_str[*i];
		*y += 1;
		*i += 1;
	}
}

int	ft_check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				return (-1);
		}
	}
	return (0);
}
