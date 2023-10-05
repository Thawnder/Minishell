/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:17:16 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/05 15:52:21 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_operator(char *str)
{
	int	op;
	int	i;

	if (!str)
		return (0);
	op = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	i += is_quoted(str, i);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '&' || str[i] == '<' || str[i] == '>')
		{
			op++;
			if (str[i + 1] == '|' || str[i + 1] == '&'
				|| str[i + 1] == '<' || str[i + 1] == '>')
				i++;
		}
		i++;
		i += is_quoted(str, i);
	}
	return (op);
}

void	ft_add_lists(t_mini *mini, int i, int l, t_operator op)
{
	t_lists	*tmp;

	if (mini->args)
	{
		tmp = mini->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_calloc(1, sizeof(t_lists));
		tmp->next->previous = tmp;
		tmp = tmp->next;
	}
	else
	{
		mini->args = ft_calloc(1, sizeof(t_lists));
		tmp = mini->args;
	}
	tmp->arg = ft_strndup(&mini->line[i], ft_size_until_op(mini->line,
				i, l + i));
	if (op == OP_PIPE)
		tmp->is_pipe = 1;
	tmp->operator = op;
}

void	ft_parse_op(t_mini *mini)
{
	int		i;
	int		l;
	char	*str;

	i = 0;
	str = mini->line;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		l = i;
		while (str[i] && (str[i] != '|' && str[i] != '<' && str[i] != '&'
				&& str[i] != '>'))
		{
			i++;
			i += is_quoted(str, i);
		}
		if (str[i] && str[i + 1] && (str[i + 1] == '|' || str[i + 1] == '<'
				|| str[i + 1] == '&' || str[i + 1] == '>'))
			i++;
		ft_add_lists(mini, l, i - l, ft_find_operator(mini->line, i));
		if (str[i])
			i++;
	}
}

void	ft_init_lists(t_mini *mini)
{
	if (!mini->has_operator)
	{
		mini->args = ft_calloc(1, sizeof(t_lists));
		mini->args->arg = ft_strdup(mini->line);
	}
	else
		ft_parse_op(mini);
}

int	ft_pre_parse(t_mini *mini)
{
	if (ft_check_line(mini->line) == -1 || ft_check_operator(mini->line) == -1)
		return (0);
	mini->has_operator = ft_has_operator(mini);
	ft_init_lists(mini);
	if (!ft_bracket(mini))
		return (0);
	ft_add_num_arg(mini);
	ft_delete_space(mini);
	check_flag(mini->args->arg);
	return (1);
}
