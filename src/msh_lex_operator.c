/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:28 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 15:43:26 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// &, <, >, |, <<, >>, &&, ||

int	msh_lex_operator(t_msh_data *m_data, char *line, unsigned int *i)
{
	int	ct;
	int	nt;

	ct = msh_get_op_type(line[*i]);
	nt = msh_get_op_type(line[*i + 1]);
	if (ct == nt)
	{
		msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(msh_get_double_op_type(ct), 0));
		*i += 2;
		return (SUCCESS);
	}
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(ct, 0));
	*i += 1;
	return (SUCCESS);
}

int			msh_get_op_type(int c)
{
	if (c == '&')
		return (MSH_AMP);
	if (c == '<')
		return (MSH_LT);
	if (c == '>')
		return (MSH_GT);
	return (MSH_PIPE);
}

int			msh_get_double_op_type(int type)
{
	if (type == MSH_AMP)
		return (MSH_DAMP);
	if (type == MSH_LT)
		return (MSH_DLT);
	if (type == MSH_GT)
		return (MSH_DGT);
	return (MSH_DPIPE);
}
