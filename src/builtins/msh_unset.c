/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:46:44 by saeby             #+#    #+#             */
/*   Updated: 2023/02/11 21:31:37 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_msh_data *m_d, t_cmd *cmd)
{
	t_env_list	*var;

	if (count_args(cmd) == 2 && ft_strncmp(cmd->args[1], "PATH", 5) != 0)
	{
		var = msh_env_ptr(m_d, cmd->args[1]);
		if (!var->prev)
			m_d->env = var->next;
		else if (var->prev)
			var->prev->next = var->next;
		free(var->key);
		free(var->val);
		free(var);
	}
	if (m_d->nb_cmd != 1)
		exit(SUCCESS);
	return (SUCCESS);
}
