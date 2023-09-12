/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:07:27 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/12 18:58:42 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_by(char *old, char *env, int here)
{
	char	*str;
	int		i;
	int		y;

	i = -1;
	y = 0;
	str = ft_calloc(ft_strlen(old) + ft_strlen(env), sizeof(char));
	ft_printf("New len %i\n", ft_strlen(old) + ft_strlen(env));
	while (++i < here)
		str[i] = old[i];
	while (env[y])
		str[i++] = env[y++];
	here++;
	while (old[here])
		str[i++] = old[here++];
	free(old);
	return (str);
}

void	find_home(t_mini *mini, t_lists *tmp)
{
	int	i;
	(void) mini;

	i = 0;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == 126)
			tmp->arg = replace_by(tmp->arg, (get_env(mini, "HOME") + 5), i);
		if (tmp->arg[i] == '"' || tmp->arg[i] == '\'')
		{
			while (tmp->arg[i] && tmp->arg[i] != '"' && tmp->arg[i] != '\'')
				i++;
		}
		i++;
	}
}

void	ft_replace(t_mini *mini)
{
	t_lists	*tmp;
	
	tmp = mini->args;

	//printf("%s\n", (get_env(mini, "PWD") + 4));
	while (tmp)
	{
		find_home(mini, tmp);
		//find_wildcard(mini, tmp);
		//find_string_(); //"" et ''
		tmp = tmp->next;
	}
}