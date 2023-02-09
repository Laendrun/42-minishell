/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:50:11 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:26:30 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	msh_lex_word(t_msh_data *m_data, char *line, unsigned int *i)
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
}*/

int	msh_lex_word(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;

	t = *i;
	while (!msh_isspace(line[*i]) && line[*i]
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(WORD, ft_strdup(tmp)));
	free(tmp);
	return (SUCCESS);
}