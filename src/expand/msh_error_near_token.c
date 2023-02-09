/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error_near_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:38:34 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/09 21:07:04 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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
	return (SUCCESS);
}