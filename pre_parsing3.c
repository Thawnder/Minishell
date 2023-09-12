/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:07:27 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/12 18:24:45 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*replace_by(char *old, char *env, int here)
{
	char	*str;
	int		i;
	int		y;

	i = 0;
	y = 0;
	str = ft_calloc(ft_strlen(old) + ft_strlen(env), sizeof(char));
	ft_printf("New len %i\n", ft_strlen(old) + ft_strlen(env));
	while (i < here)
		str[i] = old[i++];
	
	while (env[here])
		str[i++] = env[here];
	



	return (str);
}

void	find_home(t_mini *mini, t_lists *tmp)
{
	int	i;

	i = 0;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == 126)
			replace_home(tmp->arg, get_)
		if (tmp->arg[i] == '"' || tmp->arg[i] == '\'')
		{
			while (tmp->arg[i] && tmp->arg[i] != '"' && tmp->arg[i] != '\'')
				i++;
		}
		i++;
	}
}*/

void	ft_replace(t_mini *mini)
{
	t_lists	*tmp;
	
	tmp = mini->args;

	while (tmp)
	{
		//find_home(mini, tmp);
		//find_wildcard(mini, tmp);
		//find_string_(); //"" et ''
		tmp = tmp->next;
	}
}