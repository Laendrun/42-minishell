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

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/

//we have to do a recursive function here !!

int	msh_malloc_new_str(t_msh_data *m_d, t_tok_list *str_tok, int flgs[3])
{
	int	i;
	char	s_part1[flg1];
	char	s_part2[flg2 - flg1];

	i = -1;
	while (++i < flg1)
		s_part1[i] = str_tok[i];
	s_part[i] = 0;
	i = -1
	while (++i < (flg2 - flg1))
		s_part2[i] = str_tok[i + 1 + flg1];
	
	


	// new[0] = malloc(sizeof(char) * new0);
	// i = -1;
	// while (++i < new0)
	// 	new[0] = str_tok[i];
	// new[0][i] = 0;
	// new[1] = malloc(sizeof(char) * (new1 - new0));
	// while (++new0 < new1)
	// 	new[1] = 


	// new[1] = try_get_var_in_env

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
				i++;
			flags[1] = i;
			//maybe useless
			// if (str_tok->val[i] == 0)
			// {
			// 	msh_malloc_new_str(m_d, str_tok, flags[0], flags[1]);
			// 	return (SUCCESS);
			// }
		}
	}
	flags[2] = i;
	msh_malloc_new_str(m_d, str_tok, flags[3]);
	// recursivity
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
			msh_flag_in_str_var(m_d, &cur);
		cur = cur->next;
	}
	return (SUCCESS);
}

/*
check  if VAR type token exists in env, if yes  the value of of var is replaced by the value
of the var in env. if it it does not exists NULL is returned.
*/

msh_replace_var_in_var(t_msh_data *m_d)
{
	t_tok_list	*cur;
	char		*new_val;

	cur = m_d->s_tok;
	while (cur->next != NULL)
	{
		if (cur->type == MSH_VAR)
		{
			new_val = malloc(sizeof(char) * (msh_get_env_var_len(m_d,cur->val) + 1));
			//prob of null returned, we have to change the function to give back something else than 0 or null!
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
	return(SUCCESS);
}