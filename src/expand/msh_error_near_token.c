/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error_near_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:38:34 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/17 10:24:12 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_start_end(t_msh_data *d)
{
	t_tok_list	*cur;

	cur = d->tokens;
	if (cur && cur->type == PIPE)
		return (msh_error(1, ERR_NEAR_TOK, 258));
	if (cur && (cur->type == GT || cur->type == DGT
			|| cur->type == LT || cur->type == DLT)
		&& !cur->next->val[0])
		return (msh_error(1, ERR_NEAR_TOK, 258));
	while (cur->next)
	{
		if (cur->type == PIPE && cur->prev && cur->prev->type >= PIPE)
			return (msh_error(1, ERR_NEAR_TOK, 258));
		cur = cur->next;
	}
	if (cur->prev && cur->prev->type >= PIPE)
		return (msh_error(1, ERR_NEAR_TOK, 258));
	return (EXIT_SUCCESS);
}

int	remove_sep(t_msh_data *d)
{
	t_tok_list	*cur;

	cur = d->tokens;
	while (cur)
	{
		if (cur->type == SEP)
			msh_remove_tok(&d->tokens, cur);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}

int	msh_err_near_token(t_msh_data *d)
{
	remove_sep(d);
	if (check_redir_start_end(d) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
