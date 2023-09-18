/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:13:18 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/18 10:44:54 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_command(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != ' ')
		return (1);
	return (0);
}

int	valid_dollars(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = -1;
	if (!has_dollar(str, 0, ft_strlen(str)))
		return (1);
	while (str[++i] && str[i] != '$')
	{
		if (str[i] == '\'')
			quote *= -1;
		while (quote != -1)
		{
			if (str[i] == '\'')
				quote *= -1;
			i++;
		}
	}
	if (str[i] == '$' && str[i + 1] == '{'
		&& (str[i + 2] == '}' || str[i + 2] == ' '))
		return (0);
	return (1);
}

int	valid_command(t_lists *tmp)
{
	if (check_builtin(tmp->arg, "exit") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "echo") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "cd") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "pwd") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "export") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "unset") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "env") == 0)
		return (1);
	else if (check_builtin(tmp->arg, "/") == 0) // Check commands.c
		return (1);
	else if (dollar_command(tmp->arg))
		return (1);
	else
		return (0);
}

char	*get_invalid_command(char *str, char c)
{
	char	*command;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (c)
	{
		while (str[y] != c)
			y++;
		while (str[i] != '}')
			i++;
	}
	else
	{
		while (str[i] && str[i] != ' ')
			i++;
	}
	command = ft_strndup(&str[y], i);
	return (command);
}

int	ft_check_advanced(t_mini *mini)
{
	t_lists	*tmp;
	char	*str;

	tmp = mini->args;
	str = NULL;
	while(tmp)
	{
		if (!valid_command(tmp))
		{
			str =  get_invalid_command(tmp->arg, 0);
			printf("%s: command not found\n", str);
			return (free(str), -1);
		}
		if (!valid_dollars(tmp->arg))
		{
			str =  get_invalid_command(tmp->arg, '$');
			printf("%s: bad substitution\n", str);
			return (free(str), -1);
		}
		tmp = tmp->next;
	}
	return(0);
}