/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:48:25 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 21:54:02 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_quotes(t_msh_data *m_data, char *line, unsigned int *i)
{
	if (line[*i] == '\'')
		return (msh_lex_squote(m_data, line, i));
	return (msh_lex_dquote(m_data, line, i));
}

int	msh_lex_squote(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	t_tok_list		*new;

	t = *i;
	new = msh_tok_lstnew(SQUOTE, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	*i += 1;
	while (ft_isprint(line[*i]) && line[*i] != '\'')
		*i += 1;
	if (line[*i] != '\'')
		return (msh_error(EXIT_ERROR, ERR_LEX_SQUO, 1));
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	new = msh_tok_lstnew(STR, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	new = msh_tok_lstnew(SQUOTE, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	*i += 1;
	free(tmp);
	return (SUCCESS);
}

int	msh_lex_dquote(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	t_tok_list		*new;

	t = *i;
	new = msh_tok_lstnew(DQUOTE, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	*i += 1;
	while (ft_isprint(line[*i]) && !(line[*i] == '\"' && line[*i - 1] != '\\'))
		*i += 1;
	if (line[*i] != '\"')
		return (msh_error(EXIT_ERROR, ERR_LEX_DQUO, 1));
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	if (!tmp)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	new = msh_tok_lstnew(STR, ft_strdup(tmp));
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	new = msh_tok_lstnew(DQUOTE, 0);
	if (!new)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	msh_tok_lstaddb(&m_data->tokens, new);
	*i += 1;
	free(tmp);
	return (SUCCESS);
}
