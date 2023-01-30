/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:18:50 by saeby             #+#    #+#             */
/*   Updated: 2023/01/30 14:54:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_parser(t_msh_data *m_data)
{
	t_tok_list	*tmp;

	tmp = m_data->s_tok;
	while (tmp->type == MSH_SEP)
		tmp = tmp->next;
	if (tmp->type == MSH_WORD)
	{
		if (msh_is_builtin(tmp->val))
			msh_exec_builtin(tmp->val, m_data);
	}
	return (SUCCESS);
}

int	msh_exec_builtin(char *str, t_msh_data *m_data)
{
	if (ft_strncmp("env", str, 4) == 0)
		msh_env(m_data);
	else if (!ft_strncmp("pwd", str, 4))
		msh_pwd(m_data);
	else if (!ft_strncmp("cd", str, 3))
		msh_cd(m_data, "/");
	else if (!ft_strncmp("export", str, 7))
		printf("Not implemented yet! (export)\n");
	else if (!ft_strncmp("unset", str, 6))
		printf("Not implemented yet! (unset)\n");
	else if (!ft_strncmp("exit", str, 5))
	{
		printf("Implemented but not used yet");
		printf(" so we can check the leaks at exit.\n");
	}
	return (SUCCESS);
}
