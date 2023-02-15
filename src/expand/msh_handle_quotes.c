/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/13 11:05:32 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_str_wrd(t_msh_data *m_d)
{
	t_tok_list	*cur;
	char		*new_val;

	cur = m_d->tokens;
	while (cur)
	{
		if ((cur->type == STR || cur->type == WORD)
			&& (cur->next->type == STR || cur->next->type == WORD))
		{
			new_val = ft_strjoin(cur->val, cur->next->val);
			if (!new_val)
				return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
			free(cur->val);
			cur->val = new_val;
			cur->type = STR;
			msh_remove_tok(&m_d->tokens, cur->next);
		}
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}

int	msh_handle_quotes(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->tokens;
	while (cur)
	{
		if (cur->type == DQUOTE || cur->type == SQUOTE)
			msh_remove_tok(&m_d->tokens, cur);
		cur = cur->next;
	}
	if (merge_str_wrd(m_d) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
