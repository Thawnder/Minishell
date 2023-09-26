/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpleutin <bpleutin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:32 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/22 12:06:43 by bpleutin         ###   ########.fr       */
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
	int		exit;
}		t_mini;

/*	Check.c	*/
void		ft_syntax_error(char *str, char c, int i);
int			ft_check_line(char *str);
/*	Check2.c	*/
int		ft_bracket(t_mini *mini);
/*	Check3.c	*/
int			ft_check_advanced(t_mini *mini);
/*	Check4.c	*/
int			ft_check_operator(char *str);
/*----------------------------------------*/
/*	pre_parsing.c	*/
int		ft_pre_parse(t_mini *mini);
/*	pre_parsing2.c	*/
void		ft_delete_space(t_mini *mini);
void		ft_add_num_arg(t_mini *mini);
/*----------------------------------------*/
/*	replace.c	*/
void		ft_replace(t_mini *mini);
/*	replace2.c	*/
void		find_quotes(t_mini *mini, t_lists *tmp);
int			has_dollar(char	*old, int i, int y);
char		*manage_dollars(t_mini *mini, char *old, int i, int y);
/*	replace3.c	*/
void		find_dollars(t_mini *mini, t_lists *tmp);
/*----------------------------------------*/
/*	parsing.c	*/
void		ft_parse(t_mini *mini);
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
char		*strdup_without(char *old, int i, int y);
char		*join_sorted(char **str, char *sep);
char		**alpha_sort_tabl(char **str);
/*	Utils4.c	*/
int			has_option_echo(char *str);
int			ft_tab_len(char **tab);
/*----------------------------------------*/
/*	Commands.c	*/
int			check_builtin(char *arg, char *ref);
void		ft_command(t_mini *mini);
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
/*----------------------------------------*/
/*	free.c	*/
void		free_tabl(char **str);

#endif
