/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:28 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 11:10:47 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// &, <, >, |, <<, >>, &&, ||, -

int	msh_lex_operator(t_msh_data *m_data, char *line, unsigned int *i)
{
	int	ct;
	int	nt;

	ct = msh_get_op_type(line[*i]);
	nt = msh_get_op_type(line[*i + 1]);

	if (ct == nt)
	{
		msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(msh_dop_type(ct), 0));
		*i += 2;
		return (SUCCESS);
	}
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(ct, 0));
	*i += 1;
	return (SUCCESS);
}

int	msh_get_op_type(int c)
{
	if (c == '&')
		return (AMP);
	if (c == '<')
		return (LT);
	if (c == '>')
		return (GT);
	if (c == '-')
		return (MINUS);
	if (c == '|')
		return (PIPE);
	return (-10);
}

int	msh_dop_type(int type)
{
	if (type == AMP)
		return (DAMP);
	if (type == LT)
		return (DLT);
	if (type == GT)
		return (DGT);
	if (type == MINUS)
		return (DMINUS);
	if (type == PIPE)
		return (DPIPE);
	return (-10);
}
