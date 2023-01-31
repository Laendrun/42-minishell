/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_escape_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/01/31 13:40:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// character that can be escaped in bash :
// \	$	`	"

int	msh_escape_char(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->s_tok;
	while (cur->next != NULL)
	{
		if ((cur->type == MSH_DQUOTE || cur->type == MSH_SQUOTE) && (cur->prev->type == MSH_WORD || cur->prev->type == MSH_STR))
		{
			
		}
		cur = cur->next;
	}

	return (SUCCESS);
}