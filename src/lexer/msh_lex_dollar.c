/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:52:43 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 15:55:19 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_dollar(t_msh_data *m_data, char *line, unsigned int *i)
{
	(void) line;
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_DOLLAR, 0));
	*i += 1;
	return (SUCCESS);
}