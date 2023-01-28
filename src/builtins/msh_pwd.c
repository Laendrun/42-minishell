/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:25:56 by saeby             #+#    #+#             */
/*   Updated: 2023/01/27 13:16:00 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_msh_data *m_data)
{
	printf("%s\n", msh_get_env(m_data, "PWD"));
	return (SUCCESS);
}

char	*msh_getpwd(t_msh_data *m_data)
{
	return (msh_get_env(m_data, "PWD"));
}

void	msh_setpwd(t_msh_data *m_data, char *new_path)
{
	msh_replace_val(m_data, "PWD", new_path);
}