/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:33:23 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 19:54:20 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free_upd(t_msh_data *m_data)
{
	printf("msh_free_upd\n");
	t_env_list	*tmp;
	int			i;

	tmp = m_data->env;
	i = 0;
	while (tmp)
	{
		printf("%s\n", m_data->env_upd[i]);
		i++;
		tmp = tmp->next;
	}
}
