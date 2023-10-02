/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:03:11 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/29 16:38:16 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lists	*delete_till_end(t_lists *tmp, t_operator op, int prio, int success)
{
	t_lists	*prev;

	while (tmp && (tmp->previous->operator == op
			|| (prio != 0 && tmp->priorities == prio)))
	{
		//ft_printf("%s | %i %i = %i et %i\n", tmp->arg, op, success, tmp->prev_or, tmp->prev_amp);
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

t_lists	*process_amp(t_mini *mini, t_lists *tmp)
{
	if (tmp->prev_or == OR_FALSE || tmp->prev_amp == AMP_FALSE)
		return (delete_till_end(tmp, tmp->previous->operator,
				tmp->priorities, -1));
	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
		tmp->next->prev_amp = AMP_FALSE;
	else
	{
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		send_command(mini, tmp);
		mini->result_value = 0;
		if (tmp->next)
			tmp->next->prev_amp = AMP_SUCCESS;
		else
			return (NULL);
	}
	tmp = tmp->next;
	if (tmp->previous->operator == OP_2AMP)
		return (process_amp(mini, tmp));
	else if (tmp->previous->operator == OP_2PIPE)
		return (process_or(mini, tmp));
	return (tmp);
}

t_lists	*process_or(t_mini *mini, t_lists *tmp)
{
	if ((tmp->prev_or == OR_SUCCESS && tmp->previous && !(tmp->previous->operator == OP_2AMP)) || tmp->prev_amp == AMP_SUCCESS)
		return (delete_till_end(tmp, tmp->previous->operator,
				tmp->priorities, 1));
	if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
	{
		if (!tmp->next)
			return (NULL);
		tmp->next->prev_or = OR_FALSE;
	}
	else
	{
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		send_command(mini, tmp);
		mini->result_value = 0;
		if (!tmp->next)
			return (NULL);
		tmp->next->prev_or = OR_SUCCESS;
	}
	if (tmp->next)
		tmp = tmp->next;
	if (tmp->previous->operator == OP_2PIPE)
		return (process_or(mini, tmp));
	else if (tmp->previous->operator == OP_2AMP)
		return (process_amp(mini, tmp));
	return (tmp);
}

void	process_arg(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		while (tmp && (tmp->operator == OP_2PIPE || tmp->operator == OP_2AMP))
		{
			if (tmp->operator == OP_2PIPE)
				tmp = process_or(mini, tmp);
			else if (tmp->operator == OP_2AMP)
				tmp = process_amp(mini, tmp);
		}
		if (!tmp)
			break ;
		if (ft_replace(mini, tmp) == -1 || ft_check_advanced(mini, tmp) == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		else
			mini->result_value = 0;
		printf("ARG = |%s| - OP %i - Arg %i - isPipe %i - Prio %i\n", tmp->arg, tmp->operator, tmp->num_arg, tmp->is_pipe, tmp->priorities);
		send_command(mini, tmp);
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
	process_arg(mini);
	/*
		reloook ( ) prio

		REPLACE $?

		DO << < >> >
	*/
	
}
