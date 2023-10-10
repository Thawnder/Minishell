/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:50:33 by bpleutin          #+#    #+#             */
/*   Updated: 2023/10/10 10:30:14 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *mini)
{
	if (mini->has_operator && mini->args->operator == OP_PIPE)
		mini->exit = 0;
	else if (mini->size_args > 2)
		printf("exit: too many arguments\n");
	else
		mini->exit = 1;
}

void	ft_pwd(t_mini *mini)
{
	if (mini->has_operator && (mini->args->operator == OP_SUP
			|| mini->args->operator == OP_2SUP))
	{
		mini->args->result = malloc(ft_strlen(mini->path) + 2);
		mini->args->result = mini->path;
		mini->args->result[ft_strlen(mini->path)] = '\n';
		mini->args->result[ft_strlen(mini->path) + 1] = '\0';
	}
	else
	{
		write(1, mini->path, ft_strlen(mini->path));
		write(1, "\n", 1);
	}
	mini->result_value = 0;
}

void	ft_env(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->has_operator && (mini->args->operator == OP_SUP
			|| mini->args->operator == OP_2SUP))
	{
		while (mini->env[i])
		{
			mini->args->result = ft_strjoin(mini->args->result, mini->env[i++]);
			mini->args->result = ft_strjoin(mini->args->result, "\n");
		}
	}
	else
	{
		while (mini->env[i])
		{
			write(1, mini->env[i], ft_strlen(mini->env[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	mini->result_value = 0;
}

int	check_builtin(char *arg, char *ref)
{
	int	len;

	len = ft_strlen(ref);
	if (ft_strncmp(arg, ref, len) == 0
		&& (*(arg + len) == 0 || *(arg + len) == ' '))
		return (0);
	return (-1);
}

void	ft_command(t_mini *mini, t_lists *tmp)
{
	if (tmp->arg[0] && check_builtin(tmp->arg, "exit") == 0)
		ft_exit(mini);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "echo") == 0)
		ft_echo(mini, tmp->arg + 5);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "cd") == 0)
		ft_cd(mini, tmp->arg + 2);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "pwd") == 0)
		ft_pwd(mini);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "export") == 0)
		ft_export(mini, tmp->arg + 6);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "unset") == 0)
		ft_unset(mini, tmp->arg + 5);
	else if (tmp->arg[0] && check_builtin(tmp->arg, "env") == 0)
		ft_env(mini);
	else
		ft_fork(mini, tmp->arg, 0);
}
