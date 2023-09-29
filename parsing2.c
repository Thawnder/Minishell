/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:41:33 by ldeville          #+#    #+#             */
/*   Updated: 2023/09/28 16:28:09 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*void	from_to(t_mini *mini, t_lists *tmp)
{
	


}*/

t_lists	*special_operator(t_mini *mini, t_lists *tmp)
{
	//if (tmp->operator == OP_PIPE) //REPLACE WHEN PIPE DONE
	return (ft_command(mini, tmp), tmp);
	/*else if (tmp->operator == OP_SUP || tmp->operator == OP_2SUP)
		return (from_to(mini, tmp), tmp->next);
	else
		return (to_from(mini, tmp));*/
}