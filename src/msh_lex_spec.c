/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:46:25 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 15:48:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (, ), {, }, [, ]

int	msh_lex_spec_char(t_msh_data *m_data, char *line, unsigned int *i)
{
	int	st;

	st = msh_get_spec_type(line[*i]);
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(st, 0));
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