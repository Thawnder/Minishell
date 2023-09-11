/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:49:30 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 11:01:05 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unused_prio_num(t_lists *args)
{
	int		prio;
	t_lists	*tmp;

	tmp = args;
	prio = 1;
	while (tmp)
	{
		if (tmp->priorities == prio)
			prio++;
		tmp = tmp->next;
	}
	return (prio);
}

int	bracket_closed(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ')')
			count++;
		i++;
	}
	return (count);
}

int	bracket_opened(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count++;
		i++;
	}
	return (count);
}

int count_bracket(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			count++;
		i++;
	}
	return (count);
}

void    delete_bracket(t_lists *tmp)
{
    int		len;
    int		i;
    char	*str;

	len = ft_strlen(tmp->arg) - count_bracket(tmp->arg) + 1;
	str = ft_calloc(len, sizeof(char));
	len = 0;
	i = 0;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] != '(' && tmp->arg[i] != ')')
			str[len++] = tmp->arg[i];
		i++;
	}
	free(tmp->arg);
	tmp->arg = str;
}