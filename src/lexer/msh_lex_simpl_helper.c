/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_simpl_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 07:30:14 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 07:30:33 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_par_from_tok(char *val)
{
	char	*res;

	res = "-";
	res = ft_strjoin(res, val);
	return (res);
}

char	*msh_fn_from_tok(char *fn, char *ext)
{
	char	*res;

	res = ft_strjoin(fn, ".");
	res = ft_strjoin(res, ext);
	return (res);
}