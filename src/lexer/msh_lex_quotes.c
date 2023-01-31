/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:48:25 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 13:31:34 by saeby            ###   ########.fr       */
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

	t = *i;
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_SQUOTE, 0));
	*i += 1;
	while (ft_isprint(line[*i]) && line[*i] != '\'')
		*i += 1;
	if (line[*i] != '\'')
	{
		*i = t + 1;
		return (ERROR);
	}
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_STR, ft_strdup(tmp)));
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_SQUOTE, 0));
	*i += 1;
	free(tmp);
	return (SUCCESS);
}

int	msh_lex_dquote(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;

	t = *i;
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_DQUOTE, 0));
	*i += 1;
	while (ft_isprint(line[*i]) && !(line[*i] == '\"' && line[*i - 1] != '\\'))
		*i += 1;
	if (line[*i] != '\"')
	{
		*i = t + 1;
		return (ERROR);
	}
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_STR, ft_strdup(tmp)));
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_DQUOTE, 0));
	*i += 1;
	free(tmp);
	return (SUCCESS);
}
