/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:46:44 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 11:10:16 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_msh_data *m_d, char *key)
{
	t_env_list	*var;

	var = msh_env_ptr(m_d, key);
	if (var)
	{
		if (!var->prev)
			m_d->env = var->next;
		else if (var->prev)
			var->prev->next = var->next;
		free(var->key);
		free(var->val);
		free(var);
		// delete key from env
		return (SUCCESS);
	}
	// do nothing
	return (SUCCESS);
}
/*
	var = msh_env_ptr(m_data, key);
	if (!var->prev)
		*(m_data->env) = var->next;
	else if(var->prev)
		var->prev->next = var->next;
*/