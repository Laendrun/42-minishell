/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:59:57 by saeby             #+#    #+#             */
/*   Updated: 2023/01/28 11:00:09 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free_env(t_msh_data *m_data)
{
	t_env_list	*tmp;

	while (m_data->env)
	{
		tmp = m_data->env->next;
		free(m_data->env->key);
		free(m_data->env->val);
		free(m_data->env);
		m_data->env = tmp;
	}
}

void	msh_free_tok(t_msh_data *m_data)
{
	t_tok_list	*tmp;

	while (m_data->tokens)
	{
		tmp = m_data->tokens->next;
		free(m_data->tokens->val);
		m_data->tokens->val = NULL;
		free(m_data->tokens);
		m_data->tokens = NULL;
		m_data->tokens = tmp;
	}
}

void	msh_free_simpl_tok(t_msh_data *m_data)
{
	t_tok_list	*tmp;

	while (m_data->s_tok)
	{
		tmp = m_data->s_tok->next;
		m_data->s_tok->val = NULL;
		free(m_data->s_tok->val);
		m_data->s_tok = tmp;
	}
}
