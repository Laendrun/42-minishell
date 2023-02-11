/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:37 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 14:12:39 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_msh_data *m_d, t_cmd *cmd)
{
	t_env_list	*tmp;

	if (count_args(cmd) > 1)
	{
		f_error("env: <args[1]>: ", strerror(ENOENT), m_d);
		return (ERROR);
	}
	tmp = m_d->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	if (m_d->nb_cmd == 1)
		return (SUCCESS);
	exit(SUCCESS);
}
