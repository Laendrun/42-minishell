/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:34:05 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 09:29:49 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_isspace(int c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

int	msh_isoperator(int c)
{
	return (c == 38 || c == 60 || c == 62 || c == 124 || c == 45);
}

// (, ), {, }, [, ]
// ., @, +, !, ?, ^ 
// *, #, _, ;, :, =
// ,, /, %, \, $, ~
int	msh_isspec(int c)
{
	int	t;

	t = (c == 40 || c == 41 || c == 123 || c == 125 || c == 91 || c == 93);
	t = (t || c == 46 || c == 64 || c == 43 || c == 33 || c == 63 || c == 94);
	t = (t || c == 42 || c == 35 || c == 95 || c == 59 || c == 58 || c == 61);
	t = (t || c == 44 || c == 47 || c == 37 || c == 92 || c == 36 || c == 126);
	return (t);
}

int	msh_is_builtin(char *str)
{
	int	t;

	t = !ft_strncmp("env", str, 4);
	t = !ft_strncmp("pwd", str, 4) || t;
	t = !ft_strncmp("cd", str, 3) || t;
	t = !ft_strncmp("export", str, 7) || t;
	t = !ft_strncmp("unset", str, 6) || t;
	t = !ft_strncmp("exit", str, 5) || t;
	return (t);
}

int	msh_is_path_comp(t_tok_list *token)
{
	int	t;
	
	t = token->type == MSH_WORD;
	t = t || (token->type == MSH_SYMBOL && !ft_strncmp(token->val, ".", 2));
	t = t || (token->type == MSH_SYMBOL && !ft_strncmp(token->val, "..", 3));
	t = t || (token->type == MSH_SYMBOL && !ft_strncmp(token->val, "/", 2));
	t = t || (token->type == MSH_SYMBOL && !ft_strncmp(token->val, "~", 2));
	return (t);
}