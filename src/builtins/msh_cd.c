/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 14:09:43 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_msh_data *m_d, t_cmd *cmd)
{
	char		*dir;
	char		*tmp;
	char		*pwd;

	dir = msh_get_env(m_d, "HOME");
	tmp = NULL;
	pwd = NULL;
	if (count_args(cmd) == 2)
	{
		free(dir);
		dir = cmd->args[1];
	}
	else if (count_args(cmd) > 2)
	{
		free(dir);
		return (msh_error(EXIT_FAILURE, ERR_CD_ARGS, 1));
	}
	if (dir[0] != '/')
	{
		tmp = ft_strjoin("/", dir);
		pwd = msh_getpwd(m_d);
		dir = ft_strjoin(pwd, tmp);
		free(tmp);
		free(pwd);
	}

	if (chdir(dir) != 0)
	{
		free(dir);
		if (m_d->nb_cmd == 1)
			return (msh_error(EXIT_FAILURE, ERR_CD_CD, 1));
		exit(msh_error(EXIT_FAILURE, ERR_CD_CD, 1));
	}
	free(dir);
	msh_setpwd(m_d, getcwd(NULL, 0));
	if (m_d->nb_cmd == 1)
		return(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}
