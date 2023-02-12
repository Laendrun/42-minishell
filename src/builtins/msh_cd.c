/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 18:19:41 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_msh_data *m_d, t_cmd *cmd)
{
	char		*dir;

	dir = msh_get_env(m_d, "HOME");
	if (count_args(cmd) > 1)
	{
		free(dir);
		dir = cmd->args[1];
	}
	else if (count_args(cmd) > 2)
		return (msh_error(EXIT_FAILURE, ERR_CD_ARGS, 1));
	if (dir[0] != '/')
	{
		dir = ft_strjoin("/", dir);
		dir = ft_strjoin(msh_getpwd(m_d), dir);
	}

	if (chdir(dir) != 0)
	{
		if (m_d->nb_cmd == 1)
			return (msh_error(EXIT_FAILURE, ERR_CD_CD, 1));
		exit(msh_error(EXIT_FAILURE, ERR_CD_CD, 1));
	}
	msh_setpwd(m_d, getcwd(NULL, 0));
	if (m_d->nb_cmd == 1)
		return(EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
}


// EXIT_FAILURE => ret, ERR_CD_ARG =>, 0 =>, 1 =>