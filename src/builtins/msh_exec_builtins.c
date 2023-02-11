/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:00:02 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 16:40:08 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec_builtin(t_cmd *cmd, t_msh_data *m_d)
{
	if (ft_strncmp("env", cmd->args[0], 4) == 0)
		msh_env(m_d, cmd);
	else if (!ft_strncmp("pwd", cmd->args[0], 4))
		msh_pwd(m_d, cmd);
	else if (!ft_strncmp("echo", cmd->args[0], 5))
		msh_echo(m_d, cmd);
	else if (!ft_strncmp("cd", cmd->args[0], 3))
		msh_cd(m_d, cmd);
	else if (!ft_strncmp("export", cmd->args[0], 7))
		msh_export(m_d, cmd);
	else if (!ft_strncmp("unset", cmd->args[0], 6))
		msh_unset(m_d, cmd);
	else if (!ft_strncmp("exit", cmd->args[0], 5))
		msh_exit(m_d, SUCCESS);
	return (SUCCESS);
}

int	count_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}
