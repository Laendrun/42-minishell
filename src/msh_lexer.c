/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:12:32 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 17:20:02 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_export(t_msh_data *m_d, char *line, unsigned int *i)
{
	t_tok_list		*new;
	char			*tmp;
	unsigned int	t;

	new = msh_tok_lstnew(WORD, ft_strdup("export"));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	new = msh_tok_lstnew(SEP, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	t = *i;
	while (line[*i] != '=')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	new = msh_tok_lstnew(WORD, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	free(tmp);
	msh_tok_lstaddb(&m_d->tokens, new);
	new = msh_tok_lstnew(SEP, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	tmp = ft_substr(line, *i + 1, ft_strlen(line) - t);
	new = msh_tok_lstnew(WORD, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_d->tokens, new);
	free(tmp);
	return (EXIT_SUCCESS);
}

int	msh_lex(t_msh_data *m_d, char *line)
{
	unsigned int	i;
	int				ret;

	ret = EXIT_SUCCESS;
	i = 0;
	while (line && line[i] && ret == EXIT_SUCCESS)
	{
		if (line[i] && msh_isspace(line[i]))
			msh_tok_lstaddb(&m_d->tokens, msh_tok_lstnew(SEP, 0));
		while (line[i] && msh_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "export", 6))
		{
			i += 7;
			ret = msh_lex_export(m_d, line, &i);
			break ;
		}
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
			ret = msh_lex_quotes(m_d, line, &i);
		else if (line[i] && (line[i] == '<' || line[i] == '>'))
			ret = msh_lex_redir(m_d, line, &i);
		else if (line[i] && line[i] == '|')
			ret = msh_lex_pipe(m_d, line, &i);
		else if (line[i])
			ret = msh_lex_word(m_d, line, &i);
	}
	return (ret);
}

int	msh_get_op_type(int c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LT);
	if (c == '>')
		return (GT);
	return (-10);
}

int	msh_dop_type(int type)
{
	if (type == LT)
		return (DLT);
	if (type == GT)
		return (DGT);
	return (-10);
}

void	insert_token(t_msh_data *m_d, int type, char *val, int *err)
{
	t_tok_list	*new;

	new = msh_tok_lstnew(type, val);
	if (!new)
		*err = ERR_MALLOC;
	msh_tok_lstaddb(&m_d->tokens, new);
}
