/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 10:08:47 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_msh_data *m_data, char *new_path)
{
	char	*dir;

	dir = new_path;
	if (dir[0] != '/')
	{
		dir = ft_strjoin("/", dir);
		dir = ft_strjoin(msh_getpwd(m_data), dir);
	}
	if (chdir(dir) != 0)
		ft_putstr_fd("Not found.\n", 2);
	msh_setpwd(m_data, getcwd(NULL, 0));
	return (SUCCESS);
}