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
		return (MSH_AMP);
	if (c == '<')
		return (MSH_LT);
	if (c == '>')
		return (MSH_GT);
	if (c == '-')
		return (MSH_MINUS);
	if (c == '|')
		return (MSH_PIPE);
	return (-10);
}

int	msh_dop_type(int type)
{
	if (type == MSH_AMP)
		return (MSH_DAMP);
	if (type == MSH_LT)
		return (MSH_DLT);
	if (type == MSH_GT)
		return (MSH_DGT);
	if (type == MSH_MINUS)
		return (MSH_DMINUS);
	if (type == MSH_PIPE)
		return (MSH_DPIPE);
	return (-10);
}
