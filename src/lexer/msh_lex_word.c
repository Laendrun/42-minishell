/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:50:11 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 20:23:23 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;

	t = *i;
	while (ft_isalnum(line[*i]))
		*i += 1;
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_WORD, ft_substr(line, t, *i - t)));
	return (SUCCESS);
}
