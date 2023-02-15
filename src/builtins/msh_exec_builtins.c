/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:00:02 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 13:48:29 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec_builtin(t_cmd *cmd, t_msh_data *m_d)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (ft_strncmp("env", cmd->args[0], 4) == 0)
		ret = msh_env(m_d, cmd);
	else if (!ft_strncmp("pwd", cmd->args[0], 4))
		ret = msh_pwd(m_d, cmd);
	else if (!ft_strncmp("echo", cmd->args[0], 5))
		ret = msh_echo(m_d, cmd);
	else if (!ft_strncmp("cd", cmd->args[0], 3))
		ret = msh_cd(m_d, cmd);
	else if (!ft_strncmp("export", cmd->args[0], 7))
		ret = msh_export(m_d, cmd);
	else if (!ft_strncmp("unset", cmd->args[0], 6))
		ret = msh_unset(m_d, cmd);
	else if (!ft_strncmp("exit", cmd->args[0], 5))
		ret = msh_exit(m_d, cmd);
	return (ret);
}

int	count_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}
