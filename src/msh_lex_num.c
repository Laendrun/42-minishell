/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:19:55 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 16:29:15 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lex_num(t_msh_data *m_data, char *line, unsigned int *i)
{
	unsigned int	t;

	t = *i;
	while (ft_isdigit(line[*i]))
		*i += 1;
	msh_tok_lstaddb(&m_data->tokens, msh_tok_lstnew(MSH_NUM, ft_substr(line, t, *i - t)));
	return (SUCCESS);
}