/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:23:18 by saeby             #+#    #+#             */
/*   Updated: 2023/01/27 13:20:53 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_cd(t_msh_data *m_data, char *new_path)
{
	(void) m_data;
	char	*dir;

	dir = new_path;
	if (dir[0] != '/')
	{
		ft_strjoin("/", dir);
		ft_strjoin(msh_getpwd(m_data), dir);
	}
	if (chdir(dir) != 0)
		ft_putstr_fd("Not found.\n", 2);
	msh_setpwd(m_data, getcwd(NULL, 0));
	//msh_replace_val(m_data, "PWD", getcwd(NULL, 0));
	return (SUCCESS);
}