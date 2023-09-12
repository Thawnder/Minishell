/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:07:27 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/12 17:22:31 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_home(t_mini *mini)
{
	t_lists	*tmp;
	
	tmp = mini->args;

	while (tmp)
	{
		tmp = tmp->next;
	}
}