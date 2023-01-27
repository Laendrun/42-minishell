/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:59:57 by saeby             #+#    #+#             */
/*   Updated: 2023/01/27 17:40:42 by saeby            ###   ########.fr       */
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

	while (m_data->simpl_tok)
	{
		tmp = m_data->simpl_tok->next;
		m_data->simpl_tok->val = NULL;
		free(m_data->simpl_tok->val);
		//free(m_data->simpl_tok);
		m_data->simpl_tok = tmp;
	}
}
