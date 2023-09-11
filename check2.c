/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:32:12 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 11:23:55 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	useless_bracket(t_lists *args)
{
	t_lists *tmp;

	tmp = args;
	while (tmp)
	{
		if (has_bracket(tmp->arg) 
			&& tmp->operator != OP_2AMP && tmp->operator != OP_2PIPE)
		{
			if (!tmp->previous || (tmp->previous && tmp->previous->operator != OP_2AMP 
			&& tmp->previous->operator != OP_2PIPE))
			{
				delete_bracket(tmp);
				while (!has_bracket(tmp->arg) && tmp->previous)
				{
					delete_bracket(tmp->previous);
					tmp = tmp->previous;
				}
			}
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
		if (tmp && bracket)
		{
			bracket -= bracket_closed(tmp->arg);
			count++;
		}
		if (count && !bracket)
			add_priorities(old, tmp, count, unused_prio_num(args));
		tmp = tmp->next;
	}
}

void	ft_bracket(t_mini *mini)
{
	if (!has_bracket(mini->line))
		return ;
	useless_bracket(mini->args);
	if (!has_bracket(mini->line))
		return ;

	check_priorities(mini->args);
	//check_bracket(mini->args);
}