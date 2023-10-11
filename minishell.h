/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:32 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/11 14:47:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_operator
{
	OP_NONE	= 0,
	OP_PIPE,
	OP_2PIPE,
	OP_2AMP,
	OP_INF,
	OP_2INF,
	OP_SUP,
	OP_2SUP,
	OP_WILD
}	t_operator;

typedef enum e_amp
{
	AMP_FALSE = -1,
	AMP_NONE,
	AMP_SUCCESS,
}	t_amp;

typedef enum e_or
{
	OR_FALSE = -1,
	OR_NONE,
	OR_SUCCESS,
}	t_or;

typedef struct s_lists
{
	char			*arg;
	t_operator		operator;
	t_amp			prev_amp;
	t_or			prev_or;
	int				num_arg;
	int				is_pipe;
	char			*result;
	int				priorities;
	struct s_lists	*previous;
	struct s_lists	*next;
}	t_lists;

typedef struct s_mini
{
	char	*line;
	char	**env;
	char	**export;
	char	*oldpath;
	char	*path;
	int		size_args;
	t_lists	*args;
	int		has_operator;
	int		result_value;
	int		old_fd[2];
	int		new_fd[2];
	int		saved_stdin;
	int		saved_stdout;
	int		*pid;
	int		exit;
}		t_mini;

/* Global Variable */
extern int	g_forked;

/*	Check.c	*/
void		ft_syntax_error(char *str, char c, int i);
int			ft_check_line(char *str);
/*	Check2.c	*/
int			ft_bracket(t_mini *mini);
/*	Check3.c	*/
char		*get_invalid_command(char *str, char c);
int			valid_dollars(char *str);
int			ft_check_advanced(t_mini *mini, t_lists *tmp);
/*	Check4.c	*/
char		*get_operator_error(char *str, int i);
int			ft_other_command(t_mini *mini, t_lists *tmp);
int			ft_check_operator(char *str);
/*	Check5.c	*/
int			find_replace_exec(t_mini *mini, t_lists *tmp);
int			try_path(t_mini *mini, t_lists *tmp);
/*----------------------------------------*/
/*	pre_parsing.c	*/
int			ft_pre_parse(t_mini *mini);
/*	pre_parsing2.c	*/
void		ft_delete_space(t_mini *mini);
void		ft_add_num_arg(t_mini *mini);
/*----------------------------------------*/
/*	replace.c	*/
int			ft_replace(t_mini *mini, t_lists *tmp);
/*	replace2.c	*/
void		find_quotes(t_mini *mini, t_lists *tmp);
int			has_dollar(char	*old, int i, int y);
char		*manage_dollars(t_mini *mini, char *old, int i, int y);
/*	replace3.c	*/
void		find_dollars(t_mini *mini, t_lists *tmp);
/*----------------------------------------*/
/*	parsing.c	*/
t_lists		*process_or(t_mini *mini, t_lists *tmp);
t_lists		*process_amp(t_mini *mini, t_lists *tmp);
t_lists		*delete_till_end(t_lists *tmp,
				t_operator op, int prio, int success);
t_lists		*process_or(t_mini *mini, t_lists *tmp);
void		ft_parse(t_mini *mini);
/*	parsing2.c	*/
void		child(t_mini *mini, t_lists *tmp, int pos);
int			ft_is_builtin(t_mini *mini, t_lists *tmp);
t_lists		*special_operator(t_mini *mini, t_lists *tmp);
/*	parsing3.c	*/
t_lists		*from_to(t_mini *mini, t_lists *tmp, t_operator op, t_lists *tmp2);
t_lists		*to_from(t_mini *mini, t_lists *tmp, t_operator op, t_lists *tmp2);
/*----------------------------------------*/
/*	Utils.c	*/
int			ft_size_until_op(char *str, int i, int l);
t_operator	ft_find_operator(char *str, int l);
void		free_args(t_mini *mini);
int			ft_has_operator(t_mini *mini);
/*	Utils2.c	*/
int			unused_prio_num(t_lists *args);
int			bracket_closed(char *str);
int			bracket_opened(char *str);
void		delete_bracket(t_lists *tmp);
int			has_bracket(char *str);
/*	Utils3.c	*/
int			check_flag(char *str);
int			ft_strcmp(const char *s1, const char *s2);
char		*strdup_without(char *old, int i, int y, int nfree);
char		*join_sorted(char **str, char *sep);
char		**alpha_sort_tabl(char **str);
/*	Utils4.c	*/
int			found_command(char *path, char *str);
char		*get_path(char **tab, char *tmp);
int			with_path(char *str);
int			has_option_echo(char *str);
int			ft_tab_len(char **tab);
/*	Utils5.c	*/
t_lists		*ft_set_next(t_mini *mini, t_lists *tmp);
void		error_path_cd(t_mini *mini, char *path);
t_lists		*send_command(t_mini *mini, t_lists *tmp);
void		add_is_pipe(t_mini *mini);
int			is_exec(char *path, char *str);
/*	Utils6.c	*/
char		*send_end(char *old);
int			cmp_end(char *str, char *end);
char		*ft_realloc_buff(char *buf, char tmp[1], int btotal);
int			file_exist(t_mini *mini, char *file);
/*	Utils7.c	*/
void		ft_custom_fork(t_mini *mini, char *line, int pipe, int from);
int			is_quoted(char *str, int i);
void		wait_pid(t_mini *mini);
void		add_pid(t_mini *mini, int pid);
t_lists		*do_chevron(t_mini *mini, t_lists *tmp);
/*	Utils8.c	*/
void		end_custom_fork(t_mini *mini, int pid, int pipe, int from);
t_lists		*error_command_pipe(t_mini *mini, t_lists *tmp);
int			pipe_action(t_mini *mini, t_lists *tmp);
t_lists		*end_pipe(t_mini *mini, t_lists *tmp);
void		command_exe_end(t_mini *mini, int from, int to, t_lists *tmp);
/*	Utils9.c	*/
int			ft_check_quotes(char *str);
void		ft_need_space(char *str, char *old_str, int *i, int *y);
t_lists		*get_end_chevron(t_lists **tmp);
void		prepare_next_pipe(t_mini *mini, t_lists *tmp);
/*----------------------------------------*/
/*	Commands.c	*/
int			check_builtin(char *arg, char *ref);
void		ft_command(t_mini *mini, t_lists *tmp);
/*	Commands2.c	*/
void		ft_echo(t_mini *mini, char *line);
void		ft_unset(t_mini *mini, char *arg);
/*	Commands3.c	*/
char		*get_env(t_mini *mini, char *src);
void		ft_cd(t_mini *mini, char *path);
/*	Commands4.c	*/
char		*get_export(t_mini *mini, char *src);
void		ft_export(t_mini *m, char *arg);
/*	Commands5.c	*/
void		ft_exec(t_mini *mini, char *line);
char		**init_args(char *line);
void		ft_fork(t_mini *mini, char *line, int pipe, pid_t pid);
/*----------------------------------------*/
/*	free.c	*/
void		free_tabl(char **str);

#endif