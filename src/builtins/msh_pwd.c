/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:25:56 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 22:45:51 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_msh_data *m_data)
{
	printf("%s\n", msh_get_env(m_data, "PWD"));
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
