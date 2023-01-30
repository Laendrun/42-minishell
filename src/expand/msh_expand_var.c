/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2022/11/21 18:51:06 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A priori je peux utiliser msh_get_env 
// int	check_env_for_var(t_msh_data *m_d)
// {
// 	t_env_list	*cur = m_d->env;

// 	while(cur->next != NULL)
// 	{
// 		printf("", );
// 		cur = cur->next;
// 	}
	
// 	return(SUCCESS);
// }

int	msh_expand_var(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d

	check_env_for_var(m_d);

	return(SUCCESS);
}