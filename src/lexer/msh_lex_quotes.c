/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:48:25 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:39:25 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_quotes(t_msh_data *m_data, char *line, unsigned int *i)
{
	if (line[*i] == '\'')
		return (msh_lex_squote(m_data, line, i));
	return (msh_lex_dquote(m_data, line, i));
}

int	msh_lex_squote(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	int				err;

	err = EXIT_SUCCESS;
	t = *i;
	insert_token(m_d, SQUOTE, 0, &err);
	*i += 1;
	while (ft_isprint(line[*i]) && line[*i] != '\'')
		*i += 1;
	if (line[*i] != '\'')
		return (msh_error(EXIT_ERROR, ERR_LEX_SQUO, 1));
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	insert_token(m_d, STR, ft_strdup(tmp), &err);
	free(tmp);
	insert_token(m_d, SQUOTE, 0, &err);
	*i += 1;
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}

int	msh_lex_dquote(t_msh_data *m_d, char *line, unsigned int *i)
{
	unsigned int	t;
	char			*tmp;
	int				err;

	t = *i;
	err = EXIT_SUCCESS;
	insert_token(m_d, DQUOTE, 0, &err);
	*i += 1;
	while (ft_isprint(line[*i]) && !(line[*i] == '\"' && line[*i - 1] != '\\'))
		*i += 1;
	if (line[*i] != '\"')
		return (msh_error(EXIT_ERROR, ERR_LEX_DQUO, 1));
	tmp = ft_substr(line, t + 1, *i - (t + 1));
	if (!tmp)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	insert_token(m_d, STR, ft_strdup(tmp), &err);
	insert_token(m_d, DQUOTE, 0, &err);
	*i += 1;
	free(tmp);
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}
