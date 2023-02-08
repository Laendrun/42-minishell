/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lex_simpl_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 07:30:14 by saeby             #+#    #+#             */
/*   Updated: 2023/02/08 16:17:21 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_par_from_tok(char *val)
{
	size_t	len;
	char	*res;

	len = ft_strlen(val) + 2;
	res = (char *) ft_calloc(len, sizeof(char));
	ft_strlcat(res, "-", len);
	ft_strlcat(res, val, len);
	return (res);
}

char	*msh_fn_from_tok(char *fn, char *ext)
{
	size_t	len;
	char	*res;

	len = ft_strlen(fn) + ft_strlen(ext) + 2;
	res = (char *) ft_calloc(len, sizeof(char));
	ft_strlcat(res, fn, len);
	ft_strlcat(res, ".", len);
	ft_strlcat(res, ext, len);
	return (res);
}
