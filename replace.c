/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:07:27 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/13 15:13:37 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_by(char *old, char *env, int here, int is_malloc)
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
	if (is_malloc)
		free(env);
	return (free(old), str);
}

void	find_home(t_mini *mini, t_lists *tmp)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == '\'' || tmp->arg[i] == '"')
			quote *= -1;
		if (quote == -1 && tmp->arg[i] == 126)
			tmp->arg = replace_by(tmp->arg, (get_env(mini, "HOME") + 5), i, 0);
		i++;
	}
}

char	*get_dir_content(char *dir)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*str;

	dirp = opendir(dir);
	if (dirp == NULL)
	{
		printf("couldn't open '%s'", dir);
		return (NULL);
	}
	dp = readdir(dirp);
	str = ft_calloc(1, sizeof(char));
	while (dp)
	{
		if (dp->d_name[0] != '.')
		{
			str = ft_strjoin(str, dp->d_name);
			str = ft_strjoin(str, " ");
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	return (join_sorted(alpha_sort_tabl(ft_split(str, ' ')), " "));
}

void	find_wildcard(t_lists *tmp)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == '\'' || tmp->arg[i] == '"')
			quote *= -1;
		if (quote == -1 && tmp->arg[i] == '*')
			tmp->arg = replace_by(tmp->arg, get_dir_content("."), i, 1);
		i++;
	}
}

void	ft_replace(t_mini *mini)
{
	t_lists	*tmp;

	tmp = mini->args;
	while (tmp)
	{
		find_home(mini, tmp);
		find_wildcard(tmp);
		find_quotes(mini, tmp);
		tmp = tmp->next;
	}
}
