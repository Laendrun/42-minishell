/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:46:36 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:46:44 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_vars(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;

	*i += 1;
	t = *i;
	while (line[*i] && !msh_isspace(line[*i]))
		*i += 1;
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(VAR, ft_substr(line, t, *i - t)));
	return (SUCCESS);
}
