/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:19:11 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/09 15:55:12 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!has_option_echo(str))
		return (0);
	while (str[i] == ' ' || (str[i] == '-'
			&& str[i + 1] != '-') || str[i] == 'n')
	{
		count++;
		i++;
	}
	while (str[i - 1] && str[i - 1] != ' ')
	{
		i--;
		count--;
	}
	return (count);
}

char	*strdup_without(char *old, int i, int y)
{
	char	*str;
	int		a;
	int		z;

	a = 0;
	z = -1;
	str = ft_calloc(ft_strlen(old) - 1, sizeof(char));
	while (old[++z])
	{
		if (z != i && z != y)
			str[a++] = old[z];
	}
	return (str);
}

char	*join_sorted(char **str, char *sep)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		line = ft_strjoin(line, str[i]);
		if (str[++i])
			line = ft_strjoin(line, sep);
	}
	free_tabl(str);
	return (line);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char	**alpha_sort_tabl(char **str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		y = i;
		while (str[i + 1])
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				tmp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = tmp;
				y = -1;
				break ;
			}
			i++;
		}
		i = y + 1;
	}
	return (str);
}
