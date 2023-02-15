/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 19:15:27 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_dir(t_msh_data *m_d, char *dir);
static int	end(t_msh_data *m_d, int status, char *dir);

int	msh_cd(t_msh_data *m_d, t_cmd *cmd)
{
	char	*dir;

	dir = msh_get_env(m_d, "HOME");
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
		dir = set_dir(m_d, dir);
	if (chdir(dir) != 0)
		return (end(m_d, EXIT_FAILURE, dir));
	msh_setpwd(m_d, getcwd(NULL, 0));
	return (end(m_d, EXIT_SUCCESS, dir));
}

static char	*set_dir(t_msh_data *m_d, char *dir)
{
	char	*tmp;
	char	*pwd;

	tmp = ft_strjoin("/", dir);
	pwd = msh_getpwd(m_d);
	dir = ft_strjoin(pwd, tmp);
	free(tmp);
	free(pwd);
	return (dir);
}

static int	end(t_msh_data *m_d, int status, char *dir)
{
	free(dir);
	if (status == EXIT_SUCCESS && m_d->nb_cmd == 1)
		return (status);
	else if (status == EXIT_SUCCESS && m_d->nb_cmd > 1)
		exit(status);
	if (status != EXIT_SUCCESS && m_d->nb_cmd == 1)
		return (msh_error(EXIT_FAILURE, ERR_CD_CD, EXIT_FAILURE));
	else if (status != EXIT_SUCCESS && m_d->nb_cmd > 1)
		exit(msh_error(EXIT_FAILURE, ERR_CD_CD, EXIT_FAILURE));
	return (EXIT_FAILURE);
}
