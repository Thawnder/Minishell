/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:06 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/11 13:55:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_other_command(t_mini *mini, t_lists *tmp)
{
	int		i;
	char	*str;

	i = 0;
	str = tmp->arg;
	if (str[i] == '.' || str[i] == '/')
		return (try_path(mini, tmp));
	if (!find_replace_exec(mini, tmp))
		return (0);
	return (1);
}

char	*get_operator_error(char *str, int i)
{
	int		y;
	char	*error;

	y = i;
	while (str[y] && str[y] != ' ')
	{
		if (str[i] != str[y])
			break ;
		y++;
	}
	if (str[y + 1] != ' ')
		error = ft_strndup(&str[y], 2);
	else
		error = ft_strndup(&str[y], 1);
	return (error);
}

int	check_operator(char *str, int i)
{
	int	y;

	y = i;
	while (str[y] && str[y] != ' ')
	{
		if (str[i] != str[y])
			return (0);
		y++;
	}
	return (1);
}

int	ft_check_operator(char *str)
{
	int		i;
	char	*error;

	i = 0;
	error = NULL;
	while (str[i])
	{
		if (is_quoted(str, i))
			i += is_quoted(str, i);
		if (str[i] && (str[i] == '|'
				|| str[i] == '&' || str[i] == '<' || str[i] == '>'))
		{
			if (!check_operator(str, i))
			{
				error = get_operator_error(str, i);
				return (ft_syntax_error(error, 0, 0), free(error), -1);
			}
		}
		i++;
	}
	return (1);
}
