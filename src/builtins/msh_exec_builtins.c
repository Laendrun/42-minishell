/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:00:02 by saeby             #+#    #+#             */
/*   Updated: 2023/02/08 21:04:43 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec_builtin(t_msh_data *m_d)
{
	if (ft_strncmp("env", m_d->cmds->args[0], 4) == 0)
		msh_env(m_d);
	else if (!ft_strncmp("pwd", m_d->cmds->args[0], 4))
		msh_pwd(m_d);
	else if (!ft_strncmp("echo", m_d->cmds->args[0], 5))
		printf("%sNot implemented yet%s\n", RED, RESET);
	else if (!ft_strncmp("cd", m_d->cmds->args[0], 3))
		msh_cd(m_d, m_d->cmds->args[1]);
	else if (!ft_strncmp("export", m_d->cmds->args[0], 7))
		msh_export(m_d, "TMP", msh_env_lstlast(m_d->env)->val);
	else if (!ft_strncmp("unset", m_d->cmds->args[0], 6))
		msh_unset(m_d, "TMP");
	else if (!ft_strncmp("exit", m_d->cmds->args[0], 5))
	{
		printf("Implemented but not used yet");
		printf(" so we can check the leaks at exit.\n");
	}
	return (SUCCESS);
}