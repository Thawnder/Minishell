/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:43:32 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/07 13:20:47 by bpleutin         ###   ########.fr       */
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
	char	*oldpath;
	char	*path;
	int		size_args;
	t_lists	*args;
	int		has_operator;
	int		exit;
}		t_mini;

void		ft_command(t_mini *mini);
void		ft_pre_parse(t_mini *mini);
int			ft_has_operator(t_mini *mini);
int			ft_check_line(char *str);
t_operator	ft_find_operator(char *str, int l);
int			ft_size_until_op(char *str, int i, int l);
void		ft_echo(t_mini *mini, char *line);
void		ft_cd(t_mini *mini, char *path);
void		ft_parse(t_mini *mini);
void		free_args(t_mini *mini);

void		ft_bracket(t_mini *mini);

/*	pre_parsing2.c	*/
void	ft_delete_space(t_mini *mini);
/*	Utils2.c	*/
int			unused_prio_num(t_lists *args);
int			bracket_closed(char *str);
int			bracket_opened(char *str);
void    	delete_bracket(t_lists *tmp);
int			has_bracket(char *str);
/*	Utils3.c	*/
void		ft_add_num_arg(t_mini *mini);

#endif
