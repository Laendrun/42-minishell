/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:50:11 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 21:45:55 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_word(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	t_tok_list		*new;

	t = *i;
	while (!msh_isspace(line[*i]) && line[*i]
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	if (!tmp)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	new = msh_tok_lstnew(WORD, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	free(tmp);
	return (EXIT_SUCCESS);
}