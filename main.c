/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:42:03 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/26 17:46:55 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_forked = 0;

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

void	signal_handler(int signal, siginfo_t *s, void *mini)
{
	if (signal == SIGINT && g_forked == 0)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT && g_forked == 1)
		kill(s->si_pid, signal);
	else if (signal == SIGQUIT && g_forked == 0)
	{
		free_all(mini);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_mini(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	mini->export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		mini->env[i] = ft_strdup(env[i]);
		mini->export[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = 0;
	mini->export[i] = 0;
	mini->export = alpha_sort_tabl(mini->export);
	mini->oldpath = ft_strdup(getenv("OLDPWD"));
	mini->path = ft_strdup(getenv("PWD"));
}

int	main(int argc, char **argv, char **env)
{
	t_mini				*mini;
	struct sigaction	s;

	(void)argv;
	(void)argc;
	s.sa_sigaction = signal_handler;
	s.sa_flags = SA_SIGINFO | SA_RESTART;
	mini = ft_calloc(1, sizeof(t_mini));
	ft_init_mini(mini, env);
	using_history();
	while (!mini->exit)
	{
		//int tcsetattr(fd, la structure de commandes en sah);
		sigaction(SIGINT, &s, (void *) mini);
		sigaction(SIGQUIT, &s, (void *) mini);
		mini->line = readline("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ");
		add_history(mini->line);
		if (ft_pre_parse(mini))
			ft_command(mini);
		free_args(mini);
	}
	rl_clear_history();
	free_all(mini);
	return (0);
}
