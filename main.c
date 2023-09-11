/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:42:03 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 13:28:20 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->path)
		free(mini->path);
	/*if (mini->args->arg)
		free_lists(mini);*/
	free(mini);
}

void	ft_init_mini(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = 0;
	mini->oldpath = ft_strdup(getenv("OLDPWD"));
	mini->path = ft_strdup(getenv("PWD"));
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	(void)argv;
	(void)argc;
	mini = ft_calloc(1, sizeof(t_mini));
	ft_init_mini(mini, env);
	while (!mini->exit)
	{
		//int tcsetattr(fd, la structure de commandes en sah);
		mini->line = readline("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ");
		//add_history(mini->line);
		ft_pre_parse(mini);
		ft_command(mini);
		free_args(mini);
	}
	free_all(mini);
	return (0);
}
