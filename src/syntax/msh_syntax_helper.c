/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:38:59 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 14:57:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_count_quotes(t_msh_data *m_d)
{
	if (msh_count_dquote(m_d) != 0)
		return (ERROR);
	if (msh_count_squote(m_d) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	msh_count_dquote(t_msh_data *m_d)
{
	t_tok_list	*tmp;
	int			count;

	count = 0;
	tmp = m_d->s_tok;
	while (tmp)
	{
		if (tmp->type == DQUOTE)
			count++;
		tmp = tmp->next;
	}
	if (count % 2 == 1)
		return (msh_error(m_d, ERR_SYNT, "syntax error caused by odd number of double quote", NULL));
	return (SUCCESS);
}

int	msh_count_squote(t_msh_data *m_d)
{
	t_tok_list	*tmp;
	int			count;

	count = 0;
	tmp = m_d->s_tok;
	while (tmp)
	{
		if (tmp->type == SQUOTE)
			count++;
		tmp = tmp->next;
	}
	if (count % 2 == 1)
		return (msh_error(m_d, ERR_SYNT, "syntax error caused by odd number of single quote", NULL));
	return (SUCCESS);
}
