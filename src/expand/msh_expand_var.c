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

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/

int	msh_malloc_new_str(t_msh_data *m_d, t_tok_list *str_tok, int flg[3])
{
	char	*s_part[3];
	char	*replaced_var;
	char	*str_joined[2];

	s_part[0] = ft_substr(str_tok->val, 0, flg[0]);
	s_part[1] = ft_substr(str_tok->val, (flg[0] + 1), (flg[1] - flg[0] - 1));
	s_part[2] = ft_substr(str_tok->val, flg[1], (flg[2] - flg[1]));
	replaced_var = ft_calloc(sizeof(char), (msh_get_env_var_len(m_d, s_part[1]) + 1));
	replaced_var = msh_get_env(m_d, s_part[1]);
	free(s_part[1]);
	str_joined[0] = ft_strjoin(s_part[0], replaced_var);
	// free(replaced_var); //does not like being freed sometimes !
	str_joined[1] = ft_strjoin(str_joined[0], s_part[2]);
	// free(str_tok->val); //does not like being freed sometimes !
	str_tok->val = ft_strdup(str_joined[1]);
	free(str_joined[0]);
	free(str_joined[1]);
	free(s_part[0]);
	free(s_part[2]);
	return (SUCCESS);
}

int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *str_tok)
{
	int	i;
	int flags[3];

	i = -1;
	while (str_tok->val[++i])
	{
		if (str_tok->val[i] == '$' && str_tok->val[i + 1] != 0)
		{
			flags[0] = i;
			i++;
			while (str_tok->val[i] && !msh_isspace(str_tok->val[i]))
			{
				if (str_tok->val[i] == '$')
					break ;
				i++;
			}
			flags[1] = i;
		}
	}
	flags[2] = i;
	msh_malloc_new_str(m_d, str_tok, flags);
	i = -1;
	while (str_tok->val[++i])
		if (str_tok->val[i] == '$')
			msh_flag_in_str_var(m_d, str_tok);
	return (SUCCESS);
}

int	msh_replace_var_in_str(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->s_tok;
	while (cur->next != NULL)
	{
		if (cur->type == MSH_STR)
			msh_flag_in_str_var(m_d, cur);
		cur = cur->next;
	}
	return (SUCCESS);
}

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/

int	msh_replace_var_in_var(t_msh_data *m_d)
{
	t_tok_list	*cur;
	char		*new_val;

	cur = m_d->s_tok;
	while (cur->next != NULL)
	{
		if (cur->type == MSH_VAR)
		{
			new_val = ft_calloc(sizeof(char), (msh_get_env_var_len(m_d,cur->val) + 1));
			new_val = msh_get_env(m_d,cur->val);
			free(cur->val);
			cur->val = new_val;
		}
		cur = cur->next;
	}
	return (SUCCESS);
}

int	msh_expand_var(t_msh_data *m_d)
{
	msh_replace_var_in_var(m_d);
	msh_replace_var_in_str(m_d);
	print_simpl_tok(m_d);
	return(SUCCESS);
}