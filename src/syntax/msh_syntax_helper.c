/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:38:59 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 13:27:31 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_count_quotes(t_msh_data *m_d)
{
	msh_count_dquote(m_d);
	msh_count_squote(m_d);
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
		if (tmp->type == MSH_DQUOTE)
			count++;
		tmp = tmp->next;
	}
	if (count % 2 == 1)
		printf("%sSyntax error: odd number of double quotes.%s\n", RED, RESET);
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
		if (tmp->type == MSH_SQUOTE)
			count++;
		tmp = tmp->next;
	}
	if (count % 2 == 1)
		printf("%sSyntax error: odd number of single quotes.%s\n", RED, RESET);
	return (SUCCESS);
}
