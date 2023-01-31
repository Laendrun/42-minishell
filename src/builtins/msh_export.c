/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:24:41 by saeby             #+#    #+#             */
/*   Updated: 2023/01/31 10:46:36 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_export(t_msh_data *m_d, char *key, char *val)
{
	t_env_list	*var;
	char		*tmp;

	var = msh_env_ptr(m_d, key);
	if (var)
	{
		tmp = var->val;
		var->val = ft_strdup(val);
		free(tmp);
		return (SUCCESS);
	}
	msh_env_lstaddb(&m_d->env, msh_env_lstnew(ft_strdup(key), ft_strdup(val)));
	return (SUCCESS);
}
