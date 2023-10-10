/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:03:11 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 22:35:51 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lists	*delete_till_end(t_lists *tmp, t_operator op, int prio, int success)
{
	t_lists	*prev;

	while (tmp && (tmp->previous->operator == op
			|| (prio != 0 && tmp->priorities == prio)))
	{
		if (tmp->previous->previous)
		{
			tmp->previous->previous->next = tmp;
			prev = tmp->previous->previous;
			free(tmp->previous->arg);
			free(tmp->previous);
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
		tmp = send_command(mini, tmp);
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
	if ((tmp->prev_or == OR_SUCCESS && tmp->previous
			&& !(tmp->previous->operator == OP_2AMP))
		|| tmp->prev_amp == AMP_SUCCESS)
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
		tmp = send_command(mini, tmp);
		mini->result_value = 0;
		if (!tmp || !tmp->next)
			return (NULL);
		tmp->next->prev_or = OR_SUCCESS;
	}
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
		ft_printf("SENDING ARG |%s|\n", tmp->arg);
		tmp = send_command(mini, tmp);
		if (tmp)
			tmp = tmp->next;
	}
}

void	ft_parse(t_mini *mini)
{
	add_is_pipe(mini);
	process_arg(mini);
	/*
		NEED TO WORK :
		
		chevrons

		CTRL+\ apres avoir écrit des choses

		Gestion des ; dans les double quotes
		
		-> Exécutez une commande simple avec des arguments, 
		mais cette fois utilisez des guillemets 
		"(rajoutez des ';' et des espaces entre les guillemets)" wtf????

		echo '    lol' (pour l'instant ça skip les espaces alors que ça devrait pas)

		unset PATH -> si on utilise une commande (ls) ça segfault

		Gérer les "''" et les '""' (simple quote dans double quote et vice versa)
		
		||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		
		NOT IMPORTANT :
		
		CTRL+C après un "echo -n"
		
		relook ( ) prio
	*/
}
