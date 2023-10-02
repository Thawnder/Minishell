/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/02 18:09:34 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_mini *mini, t_lists *tmp, int pos)
{
	ft_printf("POS %i\n", pos);
	if (pipe(mini->old_fd) < 0)
		return ;
	if (pos == 0)
	{
		write(1, "1", 1);
		dup2(mini->old_fd[1], 1);
		write(2, "2", 1);
		ft_fork(mini, tmp->arg);
		write(2, "3", 1);
		close(mini->old_fd[1]);
		ft_printf("ergertgert\n");
	}
	else if (pos == 1)
	{
		dup2(mini->new_fd[0], 0);
		dup2(mini->old_fd[1], 1);
		ft_fork(mini, tmp->arg);
		close(mini->new_fd[0]);
		close(mini->old_fd[1]);
	}
	else
	{
		write(2, "7", 1);
		dup2(mini->new_fd[0], 0);
		ft_fork(mini, tmp->arg);
	}
	fprintf(stderr, "\n%i et %i\n", mini->new_fd[0], mini->new_fd[1]);
	fprintf(stderr, "\n%i et %i\n", mini->old_fd[0], mini->old_fd[1]);
	mini->new_fd[0] = mini->old_fd[0];
	mini->new_fd[1] = mini->old_fd[1];
	write(2, "5", 1);
}

t_lists	*ft_pipe(t_mini *mini, t_lists *tmp)
{
	mini->new_fd[0] = 0;
	mini->new_fd[1] = 0;
	while (tmp && (tmp->operator == OP_PIPE
		|| (tmp->previous && tmp->previous->operator == OP_PIPE)))
	{
		write(2, "6", 1);
		if (!tmp->previous || (tmp->previous && tmp->previous->operator != OP_PIPE))
			child(mini, tmp, 0);
		else if (tmp->next && tmp->next->operator == OP_PIPE)
			child(mini, tmp, 1);
		else if (!tmp->next || (tmp->next && tmp->next->operator != OP_PIPE))
			child(mini, tmp, 2);
		tmp = tmp->next;
	}
	write(2, "10", 2);
	ft_printf("ergertgert\n");
	return (tmp);
}

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	if (tmp->operator == OP_PIPE)
		return (ft_pipe(mini, tmp));
	// else if (tmp->operator == OP_SUP || tmp->operator == OP_2SUP)
	// 	return (from_to(mini, tmp), tmp->next);
	// else
	// 	return (to_from(mini, tmp));
	
	
	return (tmp);
}
