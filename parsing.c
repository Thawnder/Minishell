/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:03:11 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/28 11:22:01 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	amp_or(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		/*if (tmp->operator == OP_2AMP || tmp->operator == OP_2PIPE)
		{
			if (ft_check_advanced(mini) != -1)
			{
				if (tmp->operator == OP_2PIPE)
					delete_next_until(tmp, OP_2PIPE);
			}
			else
			{
				if (tmp->operator == OP_2AMP)
					delete_next_until(tmp, OP_2AMP);
			}
		}*/
		tmp = tmp->next;
	}
}

t_lists	*delete_till_end(t_lists *tmp, t_operator op, int prio, int success)
{
	t_lists *prev;

	while (tmp && tmp->previous->operator == op && tmp->previous->priorities == prio)
	{
		if (tmp->previous->previous)
		{
			tmp->previous->previous->next = tmp;
			prev = tmp->previous->previous;
		}
		else
			prev = NULL;
		tmp->previous = prev;
		if (tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	if (op == OP_2PIPE)
		tmp->prev_or = success;
	else
		tmp->prev_amp = success;
	return (tmp);
}

t_lists	*process_or(t_mini *mini, t_lists *tmp)
{
	if (tmp->prev_or == OR_SUCCESS || tmp->prev_amp == AMP_SUCCESS)
		return (delete_till_end(tmp, tmp->previous->operator, tmp->previous->priorities, 1));
	
	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
	{	
		tmp->next->prev_or = OR_FALSE;
	}
	else
	{
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		if (tmp->operator == OP_PIPE || (tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))
			ft_command(mini, tmp); //replace to ft PIPE and <
		else
			ft_command(mini, tmp);
		if (tmp->next)
			tmp->next->prev_or = OR_SUCCESS;
		else
			return (NULL);
	}
	if (tmp->next)
		tmp = tmp->next;
	if (tmp->previous->operator == OP_2PIPE)
		return (process_or(mini, tmp));
	return (tmp->previous);
}

t_lists	*process_amp(t_mini *mini, t_lists *tmp)
{
	if (tmp->prev_or == OR_FALSE || tmp->prev_amp == AMP_FALSE)
		return (delete_till_end(tmp, tmp->previous->operator, tmp->previous->priorities, -1));

	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
	{
		tmp->next->prev_amp = AMP_FALSE;
	}
	else
	{
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		if (tmp->operator == OP_PIPE || (tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))
			ft_command(mini, tmp); //replace to ft PIPE and <
		else
			ft_command(mini, tmp);
		if (tmp->next)
			tmp->next->prev_amp = AMP_SUCCESS;
		else
			return (NULL);
	}
	tmp = tmp->next;
	if (tmp->previous->operator == OP_2AMP)
		return (process_amp(mini, tmp));
	return (tmp->previous);
}

void	process_arg(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		while (tmp && (tmp->operator == OP_2PIPE || tmp->operator == OP_2AMP))
		{
			if(tmp->operator == OP_2PIPE)
				tmp = process_or(mini, tmp);
			else if(tmp->operator == OP_2AMP)
				tmp = process_amp(mini, tmp);
		}
		if (!tmp)
			break ;
		if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		if (tmp->operator == OP_PIPE || (tmp->operator >= OP_INF && tmp->operator <= OP_2SUP))
			ft_command(mini, tmp); //replace to ft PIPE and <
		else
			ft_command(mini, tmp);
		tmp = tmp->next;
	}
	
	/*t_lists	*tmp2;

	tmp2 = mini->args;
	while (tmp2)
	{
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp2->arg, tmp2->operator, tmp2->num_arg, tmp2->is_pipe, tmp2->priorities);
		tmp2 = tmp2->next;
	}*/
}

void	ft_parse(t_mini *mini)
{
	add_is_pipe(mini);
	//ft_amp_or(mini);
	process_arg(mini);

	/*
		PROBLEM BONUS && || need to check during execution and not before
		
		TRY FONCTION AND ADD && AND || TRUE AND DELETE USELESS

		REPLACE $?

		DO << < >> >
	*/
	
}
