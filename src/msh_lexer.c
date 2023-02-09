/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:12:32 by saeby             #+#    #+#             */
/*   Updated: 2023/02/09 16:12:47 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	msh_lex(t_msh_data *m_data, char *line)
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
}*/

int	msh_lex_pipe(t_msh_data *m_d, char *line, unsigned int *i)
{
	(void) line;
	msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(PIPE, 0));
	*i += 1;
	return (SUCCESS);
}

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
	print_tok(m_d);
	return (SUCCESS);
}