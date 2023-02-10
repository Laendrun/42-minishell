/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 19:38:03 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_msh_data *m_d, t_cmd *cmd)
{
	char		*dir;

	printf("%sBUILTIN CD%s\n", RED, RESET);
	dir = msh_get_env(m_d, "HOME");
	if (count_args(cmd) == 2)
	{
		free(dir);
		dir = cmd->args[1];
	}
	else if (count_args(cmd) > 2)
		return (ERROR);
	if (dir[0] != '/')
	{
		dir = ft_strjoin("/", dir);
		dir = ft_strjoin(msh_getpwd(m_d), dir);
	}

	if (chdir(dir) != 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
	}
	msh_setpwd(m_d, getcwd(NULL, 0));
	return(SUCCESS);
}
