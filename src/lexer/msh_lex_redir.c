/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:45:36 by saeby             #+#    #+#             */
/*   Updated: 2023/02/12 12:29:43 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_redir(t_msh_data *m_d, char *line, unsigned int *i, int *err)
{
	unsigned int	t;
	char			*tmp;

	t = 0;
	while (msh_isspace(line[*i]) && line[*i])
		*i += 1;
	t = *i;
	while (!msh_isspace(line[*i]) && line[*i]
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	if (!tmp)
		*err = ERR_MALLOC;
	insert_token(m_d, REDIR, ft_strdup(tmp), err);
	free(tmp);
}

int	msh_lex_redir(t_msh_data *m_d, char *line, unsigned int *i)
{
	int				err;

	err = EXIT_SUCCESS;
	if (msh_get_op_type(line[*i]) == msh_get_op_type(line[*i + 1]))
	{
		insert_token(m_d, msh_dop_type(msh_get_op_type(line[*i])), 0, &err);
		*i += 2;
	}
	else
	{
		insert_token(m_d, msh_get_op_type(line[*i]), 0, &err);
		*i += 1;
	}
	get_redir(m_d, line, i, &err);
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}
