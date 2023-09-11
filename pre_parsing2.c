/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:29:46 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 16:15:28 by ldeville         ###   ########.fr       */
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
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		while (str[i] && str[i] > 32 && str[i] < 127)
		{
			if(str[i] == '"' || str[i] == '\'')
			{
				while (str[++i] && (str[i] != '"' || str[i] != '\''))
					len++;
			}
			i++;
			len++;
		}
	}
	ft_printf("len = %i", len);
	return (len);
}

char	*delete_space(char *old_str, int num_arg)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	str = ft_calloc((get_len_space(old_str) + num_arg), sizeof(char));
	while (old_str[i])
	{
		ft_printf("i = %i\n", i);
		while (old_str[i] == ' ' || (old_str[i] >= 9 && old_str[i] <= 13))
			i++;
		ft_printf("2i = %i\n", i);
		while (old_str[i] && old_str[i] > 32 && old_str[i] < 127)
		{
			ft_printf("3i = %i\n", i);
			str[y++] = old_str[i++];
			if(old_str[i - 1] == '"' || old_str[i - 1] == '\'')
			{
				while (old_str[++i] && (old_str[i - 1] != '"' || old_str[i - 1] != '\''))
					str[y++] = old_str[i];
				ft_printf("4i = %i\n", i);
			}
		}
		ft_printf("5i = %i\n", i);
		if (old_str[i] && num_arg-- > 1)
			str[y++] = ' ';
	}
	return (free(old_str), str);
}

void	ft_delete_space(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while(tmp)
	{
		tmp->arg = delete_space(tmp->arg, tmp->num_arg);
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
			if(str[i] == '"' || str[i] == '\'')
			{
				while (str[++i] && (str[i] != '"' || str[i] != '\''))
					i++;
			}
			else
				i++;
		}
	}
	return (count);
}

void ft_add_num_arg(t_mini *mini)
{
	t_lists *tmp;

	tmp = mini->args;
	while (tmp)
	{
		tmp->num_arg = get_num_arg(tmp->arg);
		tmp = tmp->next;
	}
}