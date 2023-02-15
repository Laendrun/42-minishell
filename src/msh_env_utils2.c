/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:06:57 by saeby             #+#    #+#             */
/*   Updated: 2023/02/15 22:10:33 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_env(t_msh_data *m_d, char *key, char *val, int *err)
{
	t_env_list	*new;

	new = msh_env_lstnew(key, val);
	if (!new)
		*err = ERR_MALLOC;
	msh_env_lstaddb(&m_d->env, new);
}
