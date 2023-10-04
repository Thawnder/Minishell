/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:20:59 by ldeville          #+#    #+#             */
/*   Updated: 2023/10/04 13:31:30 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	child_between_pipe(t_mini *mini, t_lists *tmp)
{
	dup2(mini->new_fd[0], 0);
	dup2(mini->old_fd[1], 1);
	ft_fork(mini, tmp->arg);
	close(mini->new_fd[0]);
	close(mini->old_fd[1]);
}