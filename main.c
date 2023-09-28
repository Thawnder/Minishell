/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:42:03 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/28 11:16:11 by bpleutin         ###   ########.fr       */
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
	rl_clear_history();
	free(mini);
}

void	signal_handler(int signal, siginfo_t *s, void *osef)
{
	(void) s;
	(void) osef;
	if (signal == SIGINT && g_forked == 0) // Ctrl + C
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT && g_forked == 1) // Ctrl + \ (untested)
		kill(s->si_pid, signal);
}

void	ft_init_all(t_mini *mini, char **env, struct sigaction s)
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
	s.sa_sigaction = signal_handler;
	s.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &s, 0);
	sigaction(SIGQUIT, &s, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini				*mini;
	struct sigaction	s;

	mini = ft_calloc(1, sizeof(t_mini));
	sigemptyset(&s.sa_mask);
	ft_init_all(mini, env, s);
	while (!mini->exit && argc && argv[0])
	{
		//int tcsetattr(fd, la structure de commandes en sah);
		mini->line = readline("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ");
		if (!mini->line) // Ctrl + D -- Same cond for STDIN while executing command?
			return (free_all(mini), 0);
		add_history(mini->line);
		if (ft_pre_parse(mini))
			ft_command(mini);
		free_args(mini);
	}
	return (free_all(mini), 0);
}
