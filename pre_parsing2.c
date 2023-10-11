/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:29:46 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/11 15:00:24 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_space(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (i != 0)
			len++;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		while (str[i] && str[i] > 32 && str[i] < 127)
		{
			len++;
			if (is_quoted(str, i))
				len += is_quoted(str, i);
			if (is_quoted(str, i))
				i += is_quoted(str, i);
			else
				i++;
		}
		while (str[i] && (str[i] <= 32 || str[i] >= 127))
			i++;
	}
	return (len);
}

char	*delete_space(char *old_str, char *str)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (old_str[i])
	{
		if (i != 0)
			str[y++] = ' ';
		while (old_str[i] == ' ' || (old_str[i] >= 9 && old_str[i] <= 13))
			i++;
		while (old_str[i] && old_str[i] > 32 && old_str[i] < 127)
		{
			str[y++] = old_str[i++];
			ft_need_space(str, old_str, &i, &y);
		}
		while (old_str[i] == ' ' || (old_str[i] >= 9 && old_str[i] <= 13))
			i++;
	}
	return (free(old_str), str);
}

void	ft_delete_space(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		tmp->arg = delete_space(tmp->arg,
				ft_calloc(get_len_space(tmp->arg) + 2,
					sizeof(char)));
		tmp = tmp->next;
	}
}

int	get_num_arg(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] > 32 && str[i] < 127)
			count++;
		while (str[i] && str[i] > 32 && str[i] < 127)
		{
			i++;
			if (is_quoted(str, i))
				i += is_quoted(str, i);
		}
	}
	return (count);
}

void	ft_add_num_arg(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		if (tmp->arg)
			tmp->num_arg = get_num_arg(tmp->arg);
		tmp = tmp->next;
	}
}
