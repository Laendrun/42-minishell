/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:25:56 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 21:37:46 by saeby            ###   ########.fr       */
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
