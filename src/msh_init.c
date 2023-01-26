/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:35:46 by saeby             #+#    #+#             */
/*   Updated: 2023/01/26 14:42:18 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_init(t_msh_data *m_data, char **env)
{
	(void) env;
	// init default values
	m_data->name = "shellusion";
	m_data->prompt = "shellusion-0.1> ";
	// init environment
	msh_env_init(m_data, env);
	return (SUCCESS);
}

int	msh_env_init(t_msh_data *m_data, char **env)
{
	// -> store every string of the environment in a linked list
	char	**tmp;
	while (*env)
	{
		tmp = ft_split(*env, '=');
		msh_env_lstaddb(&m_data->env, msh_env_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1])));
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		env++;
	}
	return (SUCCESS);
}