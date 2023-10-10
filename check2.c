/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:32:12 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/28 15:49:24 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	useless_bracket(t_lists *args)
{
	t_lists	*tmp;

	tmp = args;
	while (tmp)
	{
		if (has_bracket(tmp->arg))
		{
			if (tmp->previous)
			{
				delete_bracket(tmp);
				while (!has_bracket(tmp->arg) && tmp->previous)
				{
					delete_bracket(tmp->previous);
					tmp = tmp->previous;
				}
			}
			else
				delete_bracket(tmp);
		}
		tmp = tmp->next;
	}
}

void	add_priorities(t_lists *old, t_lists *tmp, int count, int prio_num)
{
	if (count == 1)
	{
		delete_bracket(tmp);
		old->priorities = prio_num;
	}
	else
	{
		while (count)
		{
			delete_bracket(old);
			old->priorities = prio_num;
			old = old->next;
			count--;
		}
	}
}

void	check_priorities(t_lists *args)
{
	int		count;
	int		bracket;
	t_lists	*tmp;
	t_lists	*old;

	tmp = args;
	count = 0;
	bracket = 0;
	while (tmp)
	{
		if (has_bracket(tmp->arg) && count == 0)
			bracket = bracket_opened(tmp->arg);
		if (bracket && count == 0)
			old = tmp;
		if (tmp && bracket && count++)
			bracket -= bracket_closed(tmp->arg);
		if (count && !bracket)
		{
			add_priorities(old, tmp, count, unused_prio_num(args));
			count = 0;
		}
		tmp = tmp->next;
	}
}

int	error_bracket(char *str)
{
	int		i;
	int		y;
	char	*error;

	i = 0;
	y = 0;
	if (check_builtin(str, "echo") == 0
		|| (str[0] == '(' && check_builtin(&str[1], "echo") == 0))
	{
		while (str[i] != ' ')
			i++;
		while (str[i] && str[i] != '(')
			i++;
		if (str[i] == '(')
		{
			while (str[y] && str[y] != ')')
				y++;
			error = ft_strndup(&str[i], y);
			return (ft_syntax_error(error, 0, 0), free(error), 1);
		}
	}
	return (0);
}

int	ft_bracket(t_mini *mini)
{
	if (!has_bracket(mini->line))
		return (1);
	if (error_bracket(mini->args->arg))
		return (0);
	useless_bracket(mini->args);
	if (!has_bracket(mini->line))
		return (1);
	check_priorities(mini->args);
	return (1);
}
