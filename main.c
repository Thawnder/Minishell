/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:42:03 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/02 13:41:20 by bpleutin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_forked = 0;

void	free_all(t_mini *mini, struct termios tmp)
{
	if (mini->line)
		free(mini->line);
	if (mini->path)
		free(mini->path);
	if (mini->oldpath)
		free(mini->oldpath);
	if (mini->env)
		free_tabl(mini->env);
	if (mini->export)
		free_tabl(mini->export);
	rl_clear_history();
	free(mini);
	tcsetattr(0, 0, &tmp);
}

void	signal_handler(int signal, siginfo_t *s, void *wtf)
{
	(void) wtf;
	if (signal == SIGINT)
	{
		if (g_forked == 1)
			printf("^C\n");
		else
		{
			printf("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ^C\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (signal == SIGQUIT)
	{
		if (s->si_pid == 0)
			kill(s->si_pid, signal);
		else if (g_forked == 0)
			printf("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ");
	}
}

void	ft_init_all(t_mini *mini, char **env)
{
	int					i;
	struct sigaction	s;

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
	sigemptyset(&s.sa_mask);
	s.sa_sigaction = signal_handler;
	s.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &s, 0);
	sigaction(SIGQUIT, &s, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini				*mini;
	struct termios		t;
	struct termios		tmp;

	mini = ft_calloc(1, sizeof(t_mini));
	ft_init_all(mini, env);
	tcgetattr(0, &t);
	tcgetattr(0, &tmp);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &t);
	while (!mini->exit && argc && argv[0])
	{
		mini->line = readline("🔹𝓜 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵 ⦒ ");
		if (!mini->line)
			return (free_all(mini, tmp), 0);
		add_history(mini->line);
		if (ft_pre_parse(mini))
			ft_parse(mini);
		free_args(mini);
		ft_printf("Last value : %i\n", mini->result_value);
	}
	return (free_all(mini, tmp), 0);
}
