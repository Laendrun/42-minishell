/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egauthey <egauthey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:51:04 by egauthey          #+#    #+#             */
/*   Updated: 2023/02/12 13:10:08 by egauthey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/

// int	msh_malloc_new_str(t_msh_data *m_d, t_tok_list *str_tok, int flg[3])
// {
// 	char	*s_part[3];
// 	char	*replaced_var;
// 	char	*str_joined;

// 	s_part[0] = ft_substr(str_tok->val, 0, flg[0]);
// 	s_part[1] = ft_substr(str_tok->val, (flg[0] + 1), (flg[1] - flg[0] - 1));
// 	s_part[2] = ft_substr(str_tok->val, flg[1], (flg[2] - flg[1]));
// 	replaced_var = msh_get_env(m_d, s_part[1]);
// 	free(s_part[1]);
// 	str_joined = ft_strjoin(s_part[0], replaced_var);
// 	free(str_tok->val);
// 	str_tok->val = NULL;
// 	str_tok->val = ft_strjoin(str_joined, s_part[2]);
// 	// printf("%s\n", str_tok->val);
// 	free(str_joined);
// 	free(s_part[0]);
// 	free(s_part[2]);
// 	free(replaced_var);
// 	return (SUCCESS);
// }

// int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *str_tok)
// {
// 	int	i;
// 	int flags[3];

// 	i = -1;
// 	flags[0] = 0;
// 	flags[1] = 0;
// 	flags[2] = 0;
// 	while (str_tok->val[++i])
// 	{
// 		if (str_tok->val[i] == '$' && str_tok->val[i + 1] != 0 && str_tok->val[i - 1] != '\\')
// 		{
// 			flags[0] = i;
// 			i++;
// 			while (str_tok->val[i] && !msh_isspace(str_tok->val[i]) && str_tok->val[i] != '$')
// 				i++;
// 			flags[1] = i;
// 			// i--;
// 		}
// 	}
// 	flags[2] = i;
// 	msh_malloc_new_str(m_d, str_tok, flags);
// 	i = -1;
// 	while (str_tok->val[++i])
// 		if (str_tok->val[i] == '$' && str_tok->val[i - 1] != '\\')
// 			msh_flag_in_str_var(m_d, str_tok);
// 	return (SUCCESS);
// }

int	msh_flag_in_str_var(t_msh_data *m_d, t_tok_list *tok)
{
	int		i;
	int		j;
	char	*ret;
	char	*env;
	
	i = -1;
	ret = ft_strdup("");
	j = 0;
		while (tok->val[++i])
		{
			if (tok->val[i] == '$' && tok->val[i + 1] != 0 && tok->val[i - 1] != '\\')
			{
				ret = strjoin_free(ret, ft_substr(tok->val, j, i - j));
				i++;
				j = i;
				while (tok->val[i] && !msh_isspace(tok->val[i]) && tok->val[i] != '$')
					i++;
				env = msh_get_env_free(m_d, ft_substr(tok->val, j, i - j));
				ret = strjoin_free(ret, env);
				j = i;
				i--;
			}
		}
		ret = strjoin_free(ret, ft_substr(tok->val, j, i - j));
		free(tok->val);
		tok->val = ret;
	return (SUCCESS);
}


int	msh_replace_var_in_str(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->tokens;
	while (cur->next)
	{
		if ((cur->type == STR && cur->prev->type == DQUOTE) || cur->type == WORD)
		{
			msh_flag_in_str_var(m_d, cur);
		}
		cur = cur->next;
	}
	return (SUCCESS);
}

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/



// int	msh_replace_var_in_var(t_msh_data *m_d)
// {
// 	t_tok_list	*cur;
// 	char		*new_val;

// 	cur = m_d->tokens;
// 	while (cur->next != NULL)
// 	{
// 		if (cur->type == VAR)
// 		{
// 			// new_val = ft_calloc(sizeof(char), (msh_get_env_var_len(m_d,cur->val) + 1));
// 			new_val = msh_get_env(m_d, cur->val);
// 			// if (!new_val[0])
// 			// {
// 			// 	free(new_val);
// 			// 	return (0);
// 			// }
// 			free(cur->val);
// 			cur->val = new_val;
// 		}
// 		cur = cur->next;
// 	}
// 	return (SUCCESS);
// }

int	value_error_code(t_tok_list *str_tok, int flg[3])
{
	char	*s_part[3];
	char	*replaced_var;
	char	*str_joined;

	s_part[0] = ft_substr(str_tok->val, 0, flg[0]);
	s_part[1] = ft_substr(str_tok->val, (flg[0] + 1), (flg[1] - flg[0] - 1));
	s_part[2] = ft_substr(str_tok->val, flg[1], (flg[2] - flg[1]));
	replaced_var = ft_itoa(msh_get_gcode());
	free(s_part[1]);
	str_joined = ft_strjoin(s_part[0], replaced_var);
	free(str_tok->val);
	str_tok->val = NULL;
	str_tok->val = ft_strjoin(str_joined, s_part[2]);
	free(str_joined);
	free(s_part[0]);
	free(s_part[2]);
	free(replaced_var);
	return (SUCCESS);
}

int	check_error_code(t_msh_data *m_d, t_tok_list *tok)
{
	int	i;
	int flags[3];

	i = -1;
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	while (tok->val[++i])
	{
		if (tok->val[i] == '$' && tok->val[i + 1] == '?' && tok->val[i - 1] != '\\')
		{
			flags[0] = i;
			i += 2;
			flags[1] = i;
		}
	}
	flags[2] = i;
	if (flags[0] != flags[1])
	{
		value_error_code(tok, flags);
		i = -1;
		while (tok->val[++i])
			if (tok->val[i] == '$' && tok->val[i - 1] != '\\')
				check_error_code(m_d, tok);
	}
	return (SUCCESS);
}

int	msh_replace_error_code(t_msh_data *m_d)
{
	t_tok_list	*cur;

	cur = m_d->tokens;
	while (cur->next)
	{
		if ((cur->type == STR && cur->prev->type == DQUOTE) || cur->type == WORD)
			check_error_code(m_d, cur);
		cur = cur->next;
	}
	return (SUCCESS);
}

int	msh_expand_var(t_msh_data *m_d)
{
	msh_replace_error_code(m_d);
	
	msh_replace_var_in_str(m_d);
	return(SUCCESS);
}