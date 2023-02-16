/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/16 15:11:48 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_dir(t_msh_data *m_d, char *dir);
static int	end(t_msh_data *m_d, int status, char *dir, t_cmd *cmd);
static int	cd_error(t_cmd *cmd);
static int	err_nohome(char *dir);

int	msh_cd(t_msh_data *m_d, t_cmd *cmd)
{
	char	*dir;

	dir = msh_get_env(m_d, "HOME");
	if (!dir[0] && count_args(cmd) == 1)
		return (err_nohome(dir));
	if (count_args(cmd) == 2)
	{
		free(dir);
		dir = set_dir(m_d, cmd->args[1]);
	}
	else if (count_args(cmd) > 2)
	{
		free(dir);
		return (msh_error(EXIT_FAILURE, ERR_CD_ARGS, 1));
	}
	if (chdir(dir) != 0)
		return (end(m_d, EXIT_FAILURE, dir, cmd));
	msh_setpwd(m_d, getcwd(NULL, 0));
	return (end(m_d, EXIT_SUCCESS, dir, cmd));
}

static char	*set_dir(t_msh_data *m_d, char *dir)
{
	char	*tmp;
	char	*pwd;

	if (dir[0] != '/')
	{
		tmp = ft_strjoin("/", dir);
		pwd = msh_getpwd(m_d);
		dir = ft_strjoin(pwd, tmp);
		free(tmp);
		free(pwd);
	}
	else
	{
		tmp = ft_strdup(dir);
		dir = tmp;
	}
	return (dir);
}

static int	end(t_msh_data *m_d, int status, char *dir, t_cmd *cmd)
{
	free(dir);
	if (status == EXIT_SUCCESS && m_d->nb_cmd == 1)
		return (status);
	else if (status == EXIT_SUCCESS && m_d->nb_cmd > 1)
		exit(status);
	if (status != EXIT_SUCCESS && m_d->nb_cmd == 1)
		return (cd_error(cmd));
	else if (status != EXIT_SUCCESS && m_d->nb_cmd > 1)
		exit(cd_error(cmd));
	return (EXIT_FAILURE);
}

static int	cd_error(t_cmd *cmd)
{
	ft_putstr_fd(ERR_CD_CD1, 2);
	ft_putstr_fd(cmd->args[1], 2);
	if (errno == ENOTDIR)
		ft_putstr_fd(ERR_CD_CD3, 2);
	else
		ft_putstr_fd(ERR_CD_CD2, 2);
	msh_set_gcode(EXIT_FAILURE);
	return (1);
}

static int	err_nohome(char *dir)
{
	free(dir);
	ft_putstr_fd(ERR_CD_HOME, 2);
	msh_set_gcode(EXIT_FAILURE);
	return (1);
}
