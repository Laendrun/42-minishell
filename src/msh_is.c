/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:34:05 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 18:20:41 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_isspace(int c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

int	msh_is_builtin(char *str)
{
	int	t;

	t = !ft_strncmp("env", str, 4);
	t = (!ft_strncmp("pwd", str, 4) || t);
	t = (!ft_strncmp("cd", str, 3) || t);
	t = (!ft_strncmp("export", str, 8) || t);
	t = (!ft_strncmp("unset", str, 6) || t);
	t = (!ft_strncmp("exit", str, 5) || t);
	t = (!ft_strncmp("echo", str, 5) || t);
	t = (!ft_strncmp("clear", str, 6) || t);
	return (t);
}

int	msh_is_envvar_comp(t_tok_list *token)
{
	int	t;

	t = token->type != DLT;
	t = (t || token->type != LT);
	t = (t || token->type != DGT);
	t = (t || token->type != GT);
	t = (t || ft_strncmp(token->val, "$", 2));
	return (t);
}

int	str_isalnum(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}
