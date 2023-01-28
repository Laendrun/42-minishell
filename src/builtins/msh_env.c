/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:37 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 10:09:09 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_msh_data *m_data)
{
	t_env_list	*tmp;

	tmp = m_data->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
