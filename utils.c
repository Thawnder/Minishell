/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:41:44 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/06 16:12:56 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_bracket(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

void	free_args(t_mini *mini)
{
	t_lists	*tmp;

	if (mini->args)
	{
		tmp = mini->args;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp->previous)
		{
			tmp = tmp->previous;
			free(tmp->next);
		}
		free(mini->args);
		mini->args = NULL;
	}
	free(mini->line);
	mini->line = NULL;
}

int	ft_size_until_op(char *str, int i, int l)
{
	char	c;
	int		y;

	y = 0;
	while (str[i] && i <= l)
	{
		c = str[i];
		if (c == '|' || c == '&' || c == '<' || c == '>')
			return (y);
		y++;
		i++;
	}
	return (y);
}

t_operator	ft_find_operator(char *str, int l)
{
	if (str[l] == '|' && str[l - 1] == '|')
		return (OP_2PIPE);
	else if (str[l] == '|')
		return (OP_PIPE);
	else if (str[l] == '&')
		return (OP_2AMP);
	else if (str[l] == '<' && str[l - 1] == '<')
		return (OP_2INF);
	else if (str[l] == '<')
		return (OP_INF);
	else if (str[l] == '>' && str[l - 1] == '>')
		return (OP_2SUP);
	else if (str[l] == '>')
		return (OP_SUP);
	else
		return (OP_NONE);
}

int	ft_has_operator(t_mini *mini)
{
	int		i;
	char	c;

	i = 0;
	while (mini->line[i])
	{
		c = mini->line[i];
		if (c == '|' || (c == '&' && mini->line[i + 1] == '&')
				|| c == '<' || c == '>')
			return (1);
		i++;
	}
	return (0);
}
