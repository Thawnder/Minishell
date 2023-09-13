/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:31:59 by bpleutin          #+#    #+#             */
/*   Updated: 2023/09/13 17:01:46 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_mini *mini, char *arg)
{
	int	i;
	(void)arg;
	
	i = 0;
	while (ft_strncmp(mini->env[i], "_=", 7))
			i++;
	// realloc mini->env
	// realloc mini->export
	// add arg at the end of mini->env
	// add "_="
}

void	print_export(t_mini *m)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (m->export[i])
	{
		m->args->result = ft_strjoin(m->args->result, "declare -x \"");
		m->args->result = ft_strjoin(m->args->result, m->export[i++]);
		m->args->result = ft_strjoin(m->args->result, "\"\n");
	}
	printf("%s", tmp);
	free(tmp);
}

void ft_export(t_mini *m, char *arg)
{
	int	i;

	i = 0;
	if (m->has_operator && m->args->operator == OP_PIPE)
	{
		if (!arg[0])
		{
			while (m->export[i])
			{
				m->args->result = ft_strjoin(m->args->result, "declare -x \"");
				m->args->result = ft_strjoin(m->args->result, m->export[i++]);
				m->args->result = ft_strjoin(m->args->result, "\"\n");
			}
		}
		else
			m->args->result = NULL;
	}
	else
	{
		if (!arg[0])
			print_export(m);
		else
			add_to_env(m, arg);
	}
}