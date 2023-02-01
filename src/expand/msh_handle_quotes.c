/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/01/31 13:40:10 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int
// {
// 	return (SUCCESS);
// }

int	msh_handle_quotes(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->s_tok;
	while (cur->next != NULL)
	{
		// case single quotes then no quotes
		if (cur->type == MSH_STR && cur->next->next != NULL && cur->next != NULL && cur->prev != NULL)
		{
			if (cur->type == MSH_STR && cur->next->next->type == MSH_WORD)
			{
				msh_remove_tok(&m_d->s_tok, cur->next);
				msh_remove_tok(&m_d->s_tok, cur->prev);
			}
		}

		// case no quotes then single quotes
		if (cur->type == MSH_SQUOTE && cur->prev != NULL)
		{
			if (cur->type == MSH_SQUOTE && (cur->prev->type == MSH_WORD || cur->prev->type == MSH_STR))
			{
				if (cur->next->next->type == MSH_SQUOTE)
				{
					msh_remove_tok(&m_d->s_tok, cur->next->next);
					msh_remove_tok(&m_d->s_tok, cur);
				}
			}
		}

		// case no quotes then double quotes
		if (cur->type == MSH_DQUOTE && cur->prev != NULL)
		{
			if (cur->type == MSH_DQUOTE && (cur->prev->type == MSH_WORD || cur->prev->type == MSH_STR))
			{
				if (cur->next->next->type == MSH_DQUOTE)
				{
					msh_remove_tok(&m_d->s_tok, cur->next->next);
					msh_remove_tok(&m_d->s_tok, cur);
				}
			}
		}
		
		// if (cur->type == MSH_STR && cur->next->next->next->type != NULL)
		// {
		// 		if (cur->type == MSH_STR && cur->next->next->next->type == MSH_STR)
		// 		{
		// 			msh_remove_tok(m_d->s_tok, cur->next);
		// 			msh_remove_tok(m_d->s_tok, cur);
		// 		}
		// }

		// case double double quotes
		// case double simple quotes
		// case simple & double quotes
		// case double & simple quotes
		// case double quotes then no quotes

		cur = cur->next;
	}
	return (SUCCESS);
}

 - SEG FAULT
		
		// if (cur->type == MSH_SQUOTE && cur->next->next->next != NULL && cur->next->next != NULL && cur->next != NULL)
		// {
		// 	if (cur->type == MSH_SQUOTE && cur->next->next->type == MSH_SQUOTE && (cur->next->next->next->type == MSH_WORD || cur->next->next->next->type == MSH_STR))
		// 	{
		// 		msh_remove_tok(m_d->s_tok, cur->next->next);
		// 		msh_remove_tok(m_d->s_tok, cur);
		// 	}
		// }

		// if (cur->type == MSH_STR && cur->next->next != NULL && cur->next != NULL && cur->prev != NULL)
		// {
		// 	if (cur->type == MSH_STR && cur->next->next->type == MSH_WORD)
		// 	{
		// 		msh_remove_tok(m_d->s_tok, cur->prev);
		// 		msh_remove_tok(m_d->s_tok, cur->next);
		// 	}
		// }

		// if (cur->type == MSH_SQUOTE && cur->next != NULL && cur->prev->prev != NULL)
		// {
		// 	if (cur->type == MSH_SQUOTE && cur->next->type == MSH_WORD)
		// 	{
		// 		msh_remove_tok(m_d->s_tok, cur->prev->prev);
		// 		msh_remove_tok(m_d->s_tok, cur);
		// 	}
		// }



