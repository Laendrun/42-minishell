/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error_near_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:38:34 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/09 21:56:15 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  if (temp->type == END && temp->prev && temp->prev->type > PIPE)

// {
// 	if (token_node->prev)
// 	{
// 		if (token_node->type == PIPE && token_node->prev->type == PIPE)
// 			return (true);
// 		if (token_node->type > PIPE && token_node->prev->type > PIPE)
// 			return (true);
// 		if (token_node->type == END && token_node->prev->type >= PIPE)
// 			return (true);
// 	}
// 	return (false);
// }

int	check_redir_start_end(t_msh_data *d)
{
	t_tok_list	*cur;

	cur = d->tokens;
	if (cur->type >= PIPE)
	{
		printf("syntax error near unexpected token\n");
		return (ERROR);
	}
	while (cur)
	{
		if (cur->type == PIPE && cur->next->type >= PIPE)
		{
			printf("syntax error near unexpected token\n");
			return (ERROR);
		}
		if (cur->type > PIPE && cur->next->type != REDIR)
		{
			printf("syntax error near unexpected token\n");
			return (ERROR);
		}
		cur = cur->next;
	}
	if (cur->prev->type >= PIPE)
	{
		printf("syntax error near unexpected token\n");
		return (ERROR);
	}
	return (SUCCESS);
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
	return (SUCCESS);
}

int	msh_err_near_token(t_msh_data *d)
{
	remove_sep(d);
	// check_redir_start_end(d);
	return (SUCCESS);
}