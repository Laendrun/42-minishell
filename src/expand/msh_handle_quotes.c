/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/09 16:36:43 by saeby            ###   ########.fr       */
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
		if ((cur->type == STR || cur->type == WORD) && (cur->next->type == STR || cur->next->type == WORD))
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

		// MOST PROBABLY TO BE TRASHED BUT TOOK ME SO LONG TO FIGURE IT OUT 
		// case simple & double quotes
		// case double & simple quotes
		// case double double quotes & double simple quotes
		// if (cur->type == MSH_STR && cur->next->next->next != NULL && cur->next->next->next->next != NULL && cur->next->next != NULL)
		// {
		// 		if (cur->next->next->next->type == MSH_STR)
		// 		{
		// 			msh_remove_tok(&m_d->s_tok, cur->next->next->next->next);
		// 			msh_remove_tok(&m_d->s_tok, cur->next->next);
		// 			msh_remove_tok(&m_d->s_tok, cur->next);
		// 			msh_remove_tok(&m_d->s_tok, cur->prev);
		// 		}
		// }

		// if (cur->type == MSH_SQUOTE && cur->next->next->next != NULL && cur->prev->prev != NULL && cur->next != NULL)
		// {
		// 		if (cur->type == MSH_SQUOTE && cur->next->type == MSH_SQUOTE)
		// 		{
		// 			msh_remove_tok(&m_d->s_tok, cur->next->next->next);
					
		// 			msh_remove_tok(&m_d->s_tok, cur->next);
		// 			msh_remove_tok(&m_d->s_tok, cur->prev->prev);
		// 			msh_remove_tok(&m_d->s_tok, cur);
		// 		}
		// }


		// // case single or double quotes then no quotes
		// else if (cur->type == MSH_STR && cur->next->next != NULL && cur->next != NULL && cur->prev != NULL)
		// {
		// 	if (cur->next->next->type == MSH_WORD)
		// 	{
		// 		printf("suis passe la !2\n");
		// 		msh_remove_tok(&m_d->s_tok, cur->next);
		// 		msh_remove_tok(&m_d->s_tok, cur->prev);
		// 	}
		// }

		
		
		// case no quotes then single quotes (make SEGFAULT sometimes)
		// if (cur->type == MSH_SQUOTE && cur->prev != NULL)
		// {
		// 	if (cur->type == MSH_SQUOTE && (cur->prev->type == MSH_WORD || cur->prev->type == MSH_STR))
		// 	{
		// 		if (cur->next->next->type == MSH_SQUOTE)
		// 		{
		// 			msh_remove_tok(&m_d->s_tok, cur->next->next);
		// 			msh_remove_tok(&m_d->s_tok, cur);
		// 		}
		// 	}
		// }

		// // case no quotes then double quotes (make SEGFAULT sometimes)
		// if (cur->type == MSH_DQUOTE && cur->prev != NULL)
		// {
		// 	if (cur->type == MSH_DQUOTE && (cur->prev->type == MSH_WORD || cur->prev->type == MSH_STR))
		// 	{
		// 		if (cur->next->next->type == MSH_DQUOTE)
		// 		{
		// 			msh_remove_tok(&m_d->s_tok, cur->next->next);
		// 			msh_remove_tok(&m_d->s_tok, cur);
		// 		}
		// 	}
		// }
		
		// // function that tries to unite the 2 above but again SEGFAULT fuck
		// else if (cur->type == MSH_STR && cur->prev->prev != NULL && cur->next != NULL && cur->prev != NULL)
		// {
		// 	if (cur->prev->prev->type == MSH_WORD)
		// 	{
		// 		printf("suis passe la !3\n");
		// 		msh_remove_tok(&m_d->s_tok, cur->next);
		// 		msh_remove_tok(&m_d->s_tok, cur->prev);
		// 	}
		// }
