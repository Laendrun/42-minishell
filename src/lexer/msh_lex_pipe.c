/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:48:21 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 20:07:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_pipe(t_msh_data *m_d, char *line, unsigned int *i)
{
	t_tok_list	*new;

	(void) line;
	new = msh_tok_lstnew(PIPE, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	*i += 1;
	return (EXIT_SUCCESS);
}
