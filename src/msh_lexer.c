/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:12:32 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 15:13:37 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex(t_msh_data *m_d, char *line)
{
	unsigned int	i;

	i = 0;
	while (line && line[i])
	{
		while (line[i] && msh_isspace(line[i]))
			i++;
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
			msh_lex_quotes(m_d, line, &i);
		else if (line[i] && (line[i] == '<' || line[i] == '>'))
			msh_lex_redir(m_d, line, &i);
		else if (line[i] && line[i] == '$')
			msh_lex_vars(m_d, line, &i);
		else if (line[i] && line[i] == '|')
			msh_lex_pipe(m_d, line, &i);
		else
			msh_lex_word(m_d, line, &i);
	}
	free(line);
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(END, 0));
	// print_tok(m_d);
	msh_expand_var(m_d);
	msh_escape_char(m_d);
	msh_handle_quotes(m_d);
	// print_tok(m_d);
	msh_create_commmands(m_d);
	msh_redir_op(m_d);
	msh_pipex(m_d);
	free_lst_in_trunc(m_d);
	msh_pip_reset(m_d);
	return (SUCCESS);
}
