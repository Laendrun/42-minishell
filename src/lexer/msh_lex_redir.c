/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:57:41 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 14:53:42 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_redir(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	int				ct;
	int				nt;

	nt = msh_get_op_type(line[*i + 1]);
	ct = msh_get_op_type(line[*i]);
	if (ct == nt)
	{
		msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(msh_dop_type(ct), 0));
		*i += 2;
	}
	else
	{
		msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(ct, 0));
		*i += 1;
	}
	while (msh_isspace(line[*i]) && line[*i])
		*i += 1;
	t = *i;
	while (!msh_isspace(line[*i]) && line[*i] 
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(REDIR, ft_strdup(tmp)));
	free(tmp);
	return (SUCCESS);
}
