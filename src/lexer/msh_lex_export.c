/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:23:15 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 18:49:29 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_export(t_msh_data *m_d, char *line, unsigned int *i)
{
	int				err;
	char			*tmp;
	unsigned int	t;

	err = EXIT_SUCCESS;
	*i += 7;
	if (!ft_strchr(line + *i, '='))
		return (EXIT_SUCCESS);
	insert_token(m_d, WORD, ft_strdup("export"), &err);
	insert_token(m_d, SEP, 0, &err);
	t = *i;
	while (line[*i] != '=')
		*i += 1;
	tmp = ft_substr(line, t, *i - t);
	insert_token(m_d, WORD, ft_strdup(tmp), &err);
	free(tmp);
	insert_token(m_d, SEP, 0, &err);
	tmp = ft_substr(line, *i + 1, ft_strlen(line) - t);
	insert_token(m_d, WORD, ft_strdup(tmp), &err);
	free(tmp);
	if (err)
		return (msh_error(ERR_MALLOC, ERR_MALMES, ERR_MALLOC));
	return (EXIT_SUCCESS);
}
