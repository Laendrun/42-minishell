/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:46:25 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 20:53:33 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (, ), {, }, [, ], ., @, +, !, ?, ^, *, #, _

int	msh_lex_symbol(t_msh_data *m_data, char *line, unsigned int *i)
{
	if (line[*i] == line[*i + 1])
	{
		msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_SYMBOL, ft_substr(line, *i, 2)));
		*i += 2;
		return (SUCCESS);
	}
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_SYMBOL, msh_chrdup(line[*i])));
	*i += 1;
	return (SUCCESS);
}

int	msh_get_spec_type(int c)
{
	if (c == '(')
		return (MSH_L_BR);
	if (c == ')')
		return (MSH_R_BR);
	if (c == '{')
		return (MSH_L_CBR);
	if (c == '}')
		return (MSH_R_CBR);
	if (c == '[')
		return (MSH_L_SBR);
	return (MSH_R_SBR);
}