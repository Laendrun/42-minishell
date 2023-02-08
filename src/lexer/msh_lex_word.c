/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:50:11 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 10:32:17 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;

	t = *i;
	while (ft_isalnum(line[*i]))
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(WORD, ft_strdup(tmp)));
	free(tmp);
	return (SUCCESS);
}
