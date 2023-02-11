/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:46:44 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 14:20:04 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_msh_data *m_d, t_cmd *cmd)
{
	t_env_list	*var;

	if (count_args(cmd) == 2)
	{
		// check if a key with name args[1] exists in env
		var = msh_env_ptr(m_d, cmd->args[1]);
		if (!var->prev)
			m_d->env = var->next;
		else if (var->prev)
			var->prev->next = var->next;
		free(var->key);
		free(var->val);
		free(var);
	}
	if (count_args(cmd) == 1 && m_d->nb_cmd == 1)
		return (SUCCESS);
	else if (count_args(cmd) == 1 && m_d->nb_cmd != 1)
		exit(SUCCESS);
	else if (count_args(cmd) > 2 && m_d->nb_cmd == 1)
		return (ERROR);
	else if (count_args(cmd) > 2 && m_d->nb_cmd != 1)
		exit(ERROR);
	else
		return (ERROR);
}
