/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:25:56 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 13:05:12 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_msh_data *m_data, t_cmd *cmd)
{
	char		*pwd;
	int			out;

	out = STDOUT_FILENO;
	if (cmd->out_app >= 0)
		out = cmd->out_app;
	if (cmd->out_trunc >= 0)
		out = cmd->out_trunc;
	pwd = msh_get_env(m_data, "PWD");
	write(out, pwd, ft_strlen(pwd));
	write(out, "\n", 1);
	free(pwd);
	if (m_data->nb_cmd == 1)
		return (SUCCESS);
	exit(SUCCESS);
}

char	*msh_getpwd(t_msh_data *m_data)
{
	return (msh_get_env(m_data, "PWD"));
}

void	msh_setpwd(t_msh_data *m_data, char *new_path)
{
	msh_replace_val(m_data, "PWD", new_path);
}
