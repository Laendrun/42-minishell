/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/09 14:17:05 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pas sur qu'il faut merge les 2 en 1 seul token
int	merge_str_wrd(t_msh_data *m_d)
{
	t_tok_list	*cur;
	int			len;
	char		*new_val;

	cur = m_d->tokens;
	while (cur)
	{
		if (cur->type == STR  && cur->next->type == STR)
		{
			len = ft_strlen(cur->val) + ft_strlen(cur->next->val);
			new_val = malloc(sizeof(char) * (len + 1));
			new_val = ft_strjoin(cur->val, cur->next->val);
			// free(cur->val); // causes double free sometimes
			cur->val = new_val;
			cur->type = STR;
			msh_remove_tok(&m_d->tokens, cur->next);
		}
		cur = cur->next;
	}
	return (SUCCESS);
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
	merge_str_wrd(m_d);
	return (SUCCESS);
}
