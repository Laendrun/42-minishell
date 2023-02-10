/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:37 by saeby             #+#    #+#             */
/*   Updated: 2023/02/10 17:06:16 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_msh_data *m_data)
{
	t_env_list	*tmp;

	tmp = m_data->env;
	printf("%sBUILTIN%s\n", RED, RESET);
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
