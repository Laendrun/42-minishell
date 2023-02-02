/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/01/31 13:40:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// int	msh_create_commmands(t_msh_data *m_d)
// {
// 	t_tok_list	*cur;

// 	cur = m_d->s_tok;
// 	while (cur)
// 	{
// 		if (cur->type == MSH_PIPE || cur->type == MSH_END)
// 			msh_remove_tok(&m_d->s_tok, cur);
// 		cur = cur->next;
// 	}
// 	return (SUCCESS);
// }