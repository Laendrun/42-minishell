/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:45:36 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 21:51:16 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_redir(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	t_tok_list		*new;

	if (msh_get_op_type(line[*i]) == msh_get_op_type(line[*i + 1]))
	{
		new = msh_tok_lstnew(msh_dop_type(msh_get_op_type(line[*i])), 0);
		if (!new)
			return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
		msh_tok_lstaddb(&m_d->tokens, new);
		*i += 2;
	}
	else
	{
		new = msh_tok_lstnew(msh_get_op_type(line[*i]), 0);
		if (!new)
			return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
		msh_tok_lstaddb(&m_d->tokens, new);
		*i += 1;
	}
	while (msh_isspace(line[*i]) && line[*i])
		*i += 1;
	t = *i;
	while (!msh_isspace(line[*i]) && line[*i]
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	if (!tmp)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	new = msh_tok_lstnew(REDIR, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	free(tmp);
	return (EXIT_SUCCESS);
}
