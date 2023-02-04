/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_terminate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:15:34 by saeby             #+#    #+#             */
/*   Updated: 2023/02/04 19:56:58 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_terminate(t_msh_data *m_data)
{
	if (m_data->s_tok)
		msh_free_simpl_tok(m_data);
	if (m_data->tokens)
		msh_free_tok(m_data);
	if (m_data->cmds)
		msh_free_cmds(m_data);
	if (m_data->trunc_lst)
		msh_free_trunc_lst(m_data);
	free(m_data->env_upd);
	if (m_data->env)
		msh_free_env(m_data);
}

//TO BE FREED

// in msh_malloc_new_str there are 2 malloc that needs to be freed 
