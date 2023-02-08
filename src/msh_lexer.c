/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:12:32 by saeby             #+#    #+#             */
/*   Updated: 2023/02/08 11:17:48 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if line and line[i] isspace => add separator token
* keep advancing in the string while line[i] isspace
* if line[i] == ' or " => take care of single quote and double
* quote that act differently
* if line[i] isope => lex operator, take care of double operator (< <<)
* if line[i] ispec => lex special chars
* if line[i] isalpha => lex symbol
* if line[i] == - => lex param
* else => print line[i] to see what I forgot
*/

int	msh_lex(t_msh_data *m_data, char *line)
{
	unsigned int	i;

	i = 0;
	while (line && line[i])
	{
		if (line && msh_isspace(line[i]))
			msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(SEP, 0));
		while (line[i] && msh_isspace(line[i]))
			i++;
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
			msh_lex_quotes(m_data, line, &i);
		else if (line[i] && (msh_isoperator(line[i])))
			msh_lex_operator(m_data, line, &i);
		else if (line[i] && (msh_isspec(line[i])))
			msh_lex_symbol(m_data, line, &i);
		else if (line[i] && ft_isalnum(line[i]))
			msh_lex_word(m_data, line, &i);
		else
			i++;
	}
	free(line);
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(END, 0));
	// print_tok(m_data);
	msh_simplify_tokens(m_data);
	return (SUCCESS);
}
