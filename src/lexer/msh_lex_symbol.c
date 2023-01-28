/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:46:25 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 10:38:31 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (, ), {, }, [, ], ., @, +, !, ?, ^, *, #, _

int	msh_lex_symbol(t_msh_data *m_data, char *line, unsigned int *i)
{
	t_tok_list	*t;

	if (line[*i] == line[*i + 1])
	{
		t = msh_tok_lstnew(MSH_SYMBOL, ft_substr(line, *i, 2));
		msh_tok_lstaddb(&m_data->tokens, t);
		*i += 2;
		return (SUCCESS);
	}
	t = msh_tok_lstnew(MSH_SYMBOL, ft_substr(line, *i, 1));
	msh_tok_lstaddb(&m_data->tokens, t);
	*i += 1;
	return (SUCCESS);
}